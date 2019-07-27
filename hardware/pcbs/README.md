**Lessons learned**

Possible improvements for v2.0/v1.0 Rev B of the pcbs:

1. Reverse voltage protection using power PMOS, [zener, resistor (and LED for indication?)]. **(vv important)**
2. integration of PCA9685 circuit into the pcb itself: reduce form factor and external wiring. **(vv important)**
3. For the connection portal pcb: the interrupt wires have to currently be all powered through one I-High and GND port. Rather have an array of 3 jumpers: interrupt, power, GND so that it is easier to wire and manage micro/limit switches. **(important)**
4. Use bigger (appropriately sized) vias -- comparable to the track thickness
5. Make the LED circuits brighter -- use transistors
6. Make an enclosure for the pcbs, with place for the knobs to come out.
7. Properly label all connections and components on the pcb (both sides for clarity and ease of use)
8. The number of motors is 4, but the connection portal and controller have capacity and connections for 5. This is a mismatch; keep the limit of motors to 4 if the arm design remains the same.
9. Have a port for the switch, which will interrupt the input power. This can be done by having a mount for a fuse between the switch and input power, so that traces don't have to be very thick and instead GND can go through the fuse from the switch. **(vv important)**
10. Have a dedicated place to mount the buck converter output fuse on the controller which could be a thick screw terminal, maybe. **(important)** 
11. The V+ and GND plates act like a capacitor and is dangerous for sensitive equipment or devices monitoring V+ since even after cutting the supply, V+ is floating at 1.5V or higher. Design circuitry to discharge this without overloading the supply and overheating when switched on. **(important)**
12. Arrange the terminal block for the two arms so that it is easier to wire them. one on left and the other on right.
13. Can mount the RPi on the bottom, thereby reducing the PCB footprint by a lot, and also allowing enough space for routing cables for the RPi.
14. Try using SMD components to further reduce the footprint.
15. Can have LED indicators for all the wires for visual debugging and also. Use the on-board 5V supply for that.
16. Try redesigning the pcb such that the design is completely modular. Another controller pcb can add two more arms at maximum. Therefore removing RPi from the board and having it has an optional mount is one step towards achieving this. **(vvv important)**
