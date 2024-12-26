# Arduino Motor Control System with Timer Interrupt

A sophisticated Arduino project featuring dual DC motor control with ultrasonic distance sensing, timer interrupts, and potentiometer-based speed/direction control.

## 🛠️ Components Used

- 1x Arduino Uno
- 2x DC Motors
- 1x L293D Motor Driver
- 1x HC-SR04 Ultrasonic Sensor
- 2x Potentiometers
- 1x 9V Battery
- Jumper Wires
- 1x Breadboard

## 📋 Features

- Dual DC motor control
- Timer interrupt implementation
- Ultrasonic distance monitoring
- Variable speed control
- Bidirectional motor operation
- Automatic safety shutdown
- Real-time distance monitoring

## ⚡ Pin Configuration

### Motor Driver (L293D)
Motor A:
 - Enable A: Pin 8
 - Input 1: Pin 7
 - Input 2: Pin 6

Motor B:
 - Enable B: Pin 3
 - Input 3: Pin 5
 - Input 4: Pin 4

### Sensors
Ultrasonic Sensor:
 - Trigger: Pin 9
 - Echo: Pin 10

Control Inputs:
 - Direction: A0
 - Speed: A1


## 🎮 System Parameters
 - Threshold Distance : 100 cm
 - Timer Interval : 5 seconds


## 📺 Circuit Diagram

![Cool Waasa-Rottis](https://github.com/user-attachments/assets/66343bdc-e96c-4081-9685-819b3535c7f5)


## 💡 Operation Modes

1. **Normal Operation**
   - Speed control via potentiometer
   - Direction control via potentiometer
   - Continuous monitoring of distance

2. **Safety Shutdown**
   - Distance < threshold
   - Timer interval exceeded
   - Emergency stop condition

## ⚙️ Timer Interrupt Configuration
Timer1 Setup:
 - Mode: CTC (Clear Timer on Compare Match)
 - Prescaler: 1024
 - Compare Match: 15624 (1 second interval)
 - Interrupt: TIMER1_COMPA_vect


## ⚠️ Important Notes

- Ensure proper motor driver connections
- Verify ultrasonic sensor alignment
- Check battery voltage levels
- Monitor motor current draw
- Verify interrupt timing
- Maintain proper cooling

## 🔧 Setup Instructions

1. **Hardware Setup**
   - Connect motors to L293D
   - Wire ultrasonic sensor
   - Install potentiometers
   - Connect power supply

2. **Software Configuration**
   - Set threshold distance
   - Configure timer parameters
   - Verify pin assignments
   - Test motor directions

## 🔍 Troubleshooting

| Problem | Possible Solution |
|---------|------------------|
| Motors not running | Check driver connections |
| Erratic behavior | Verify timer settings |
| Distance errors | Check sensor alignment |
| Uneven speeds | Calibrate motor outputs |

## 🔄 System States

RUNNING
 - Motors active
 - Timer counting
 - Distance monitoring

STOPPED
 - Motors disabled
 - Timer reset
 - Awaiting restart

## 📝 License

This project is licensed under the MIT License
