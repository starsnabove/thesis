all: loader


loader: bbone/pwm.o bbone/servo.o bbone/claw.o bbone/uart.o bbone/gpio.o bbone/motor.o general/drive.o general/matrix.o general/kinematics.o general/arm.o loader.o api.o
	g++ -Wall -pedantic -o loader bbone/pwm.o bbone/servo.o bbone/claw.o bbone/uart.o bbone/gpio.o bbone/motor.o general/drive.o general/matrix.o general/kinematics.o general/arm.o loader.o api.o

api.o: api.h api.cpp
	g++ -g -Wall -pedantic -fmessage-length=0 -c -o api.o api.cpp

loader.o: loader.cpp loader.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o loader.o loader.cpp

bbone/pwm.o: bbone/pwm.cpp bbone/pwm.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o bbone/pwm.o bbone/pwm.cpp

bbone/servo.o: bbone/servo.cpp bbone/servo.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o bbone/servo.o bbone/servo.cpp

bbone/claw.o: bbone/claw.cpp bbone/claw.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o bbone/claw.o bbone/claw.cpp

bbone/uart.o: bbone/uart.cpp bbone/uart.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o bbone/uart.o bbone/uart.cpp

bbone/gpio.o: bbone/gpio.cpp bbone/gpio.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o bbone/gpio.o bbone/gpio.cpp

bbone/motor.o: bbone/motor.cpp bbone/motor.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o bbone/motor.o bbone/motor.cpp

general/drive.o: general/drive.cpp general/drive.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o general/drive.o general/drive.cpp

general/matrix.o: general/matrix.cpp general/matrix.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o general/matrix.o general/matrix.cpp

general/kinematics.o: general/kinematics.cpp general/kinematics.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o general/kinematics.o general/kinematics.cpp

general/arm.o: general/arm.cpp general/arm.h
	g++ -g -Wall -pedantic  -fmessage-length=0 -c -o general/arm.o general/arm.cpp


clean:
	rm -f bbone/*.o
	rm -f general/*.o
	rm -f *.o
	rm loader
