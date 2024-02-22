#BT_HCI_RTS on FPGA /  emio_uart0_ctsn connect to 
set_property PACKAGE_PIN B7 [get_ports BT_ctsn]
#BT_HCI_CTS on FPGA / emio_uart0_rtsn
set_property PACKAGE_PIN B5 [get_ports BT_rtsn]

#HD_GPIO_0, ~CS
set_property PACKAGE_PIN D7 [get_ports SPI_0_0_ss_io]
#HD_GPIO_1, NC
set_property PACKAGE_PIN F8 [get_ports SPI_0_0_io0_io]
#HD_GPIO_2, SDO
set_property PACKAGE_PIN F7 [get_ports SPI_0_0_io1_io]
#HD_GPIO_3, SCK
set_property PACKAGE_PIN G7 [get_ports SPI_0_0_sck_io]

# Set the bank voltage for IO Bank 26 to 1.8V
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 26]];
