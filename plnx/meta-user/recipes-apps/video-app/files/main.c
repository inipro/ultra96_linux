#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <mediactl/mediactl.h>
#include <mediactl/v4l2subdev.h>
#include <gst/gst.h>

#define MEDIA_FMT "\"%s\":%d [fmt:%s/%dx%d field:none]"

void media_set_fmt_str(char *set_fmt, char *entity, unsigned int pad,
		const char *fmt, unsigned int width, unsigned int height)
{
	sprintf(set_fmt, MEDIA_FMT, entity, pad, fmt, width, height);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	char media_formats[100];
	struct media_device *media = media_device_new("/dev/media0");
	GstElement *pipeline, *source, *capsfilter, *sink;
	GstCaps *srcCaps = NULL;
	GstBus *bus;
	GstMessage *msg;
	GstStateChangeReturn ret_gst;

	if (!media) {
		fprintf(stderr, "failed to create media device from '/dev/media0'\n");
		return -1;
	}

	ret = media_device_enumerate(media);
	if (ret < 0) {
		fprintf(stderr, "failed to enumerate /dev/media0\n");
		return -1;
	}

	/* Set image sensor format */
	memset(media_formats, 0, sizeof(media_formats));
	media_set_fmt_str(media_formats, "ov5640 3-003c", 0, "UYVY", 1920, 1080);
	ret = v4l2_subdev_parse_setup_formats(media, media_formats);
	if (ret) {
		fprintf(stderr, "Unable to setup the format of \"ov5640 3-003c\": 0 : %s (%d)\n", strerror(-ret), -ret);
		goto err_mdev;
	}

	/* Set VPSS CSC format */
	memset(media_formats, 0, sizeof(media_formats));
	media_set_fmt_str(media_formats, "80020000.v_proc_ss", 0, "UYVY", 1920, 1080);
	ret = v4l2_subdev_parse_setup_formats(media, media_formats);
	if (ret) {
		fprintf(stderr, "Unable to setup the format of \"80020000.v_proc_ss\": 0 : %s (%d)\n", strerror(-ret), -ret);
		goto err_mdev;
	}

	gst_init(&argc, &argv);

	source = gst_element_factory_make("v4l2src", NULL);
	capsfilter = gst_element_factory_make("capsfilter", NULL);
	sink = gst_element_factory_make("kmssink", NULL);

	pipeline = gst_pipeline_new("video-app");

	if (!pipeline || !source || !capsfilter || !sink) {
		g_printerr("Not all elements could be created\n");
		ret = -1;
		goto err_mdev;
	}

	gst_bin_add_many(GST_BIN(pipeline), source, capsfilter, sink, NULL);
	if (!gst_element_link_many(source, capsfilter, sink, NULL)) {
		g_printerr("Elements could not be linked\n");
		gst_object_unref(pipeline);
		ret = -1;
		goto err_mdev;
	}

	srcCaps = gst_caps_new_simple("video/x-raw",
			"width", G_TYPE_INT, 1920,
			"height", G_TYPE_INT, 1080,
			"format", G_TYPE_STRING, "RGB",
			NULL);

	g_object_set(G_OBJECT(source), "device", "/dev/video0", NULL);
	g_object_set(G_OBJECT(source), "io-mode", 5, NULL);
	g_object_set(G_OBJECT(capsfilter), "caps", srcCaps, NULL);
	g_object_set(G_OBJECT(sink), "bus-id", "fd4a0000.display", NULL);
	g_object_set(G_OBJECT(sink), "plane-id", 41, NULL);

	ret_gst = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if (ret_gst == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to the playing state\n");
		gst_object_unref(pipeline);
		ret = -1;
		goto err_mdev;
	}

	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

	if (msg != NULL) {
		GError *err;
		gchar *debug_info;

		switch(GST_MESSAGE_TYPE(msg)) {
			case GST_MESSAGE_ERROR:
				gst_message_parse_error(msg, &err, &debug_info);
				g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
				g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
				g_clear_error(&err);
				g_free(debug_info);
				break;
			case GST_MESSAGE_EOS:
				g_print("End-Of-Stream reached\n");
				break;
			default:
				g_printerr("Unexpected message received\n");
				break;
		}
		gst_message_unref(msg);
	}

	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);

err_mdev:
	media_device_unref(media);

	return ret;
}
