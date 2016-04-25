"""
	Simple serial monitor for debugging

	Programmed by William Harrington
"""
import serial
import sys
import signal

def signal_handler(signal, frame):
    """Function handles signal interrupt (CTRL-C)

    :param signal: signal caught
    :param frame: current stack frame
    """
    print '\nExiting...'
    sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)

# example port for CP2102 USB2UART (MacOSX)
#port = '/dev/tty.SLAB_USBtoUART'

def main():

	# check for proper amount of arguments
	if(len(sys.argv) != 2):
		print 'Usage: python serial_monitor.py port'
		print 'where port is the serial port that the CP2102 is on'
		sys.exit(0)

	# set port to user specified value
	port = str(sys.argv[1])

	while 1:
		try:
			# read bytes from serial port
			with serial.Serial(port, 115200, timeout=2.5) as ser:
				print 'Reading bytes...'
				#x = ser.read(3)
				x = ser.readline()
				print 'Received %s' % x
		except OSError:
			# device not on port, exit out
			print 'Device not connected to port. Exting...'
			sys.exit(0)

if __name__ == "__main__":
	main()
