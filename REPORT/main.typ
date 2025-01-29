#import "template.typ": *
#import "colorbox.typ": colorbox
#import "@preview/riesketcher:0.2.1": riesketcher
#import "@preview/gentle-clues:1.0.0": *

// #let L_C = "𝓛";

// Take a look at the file `template.typ` in the file panel
// to customize this template and discover how it works.
#show: project.with(
  school:"Poznan University of Technology",
  faculty: "Faculty of Control, Robotics" + linebreak() + "and Electrical Engineering",
  institute : "Institute of Robotics and Machine Intelligence" + linebreak() + "Division of Control and Industrial Electronics
",
  course_type: "Report",
  course: "Microprocessor Systems" ,
  authors: (
    (name: "Gaby Bourges", email: "gbourges@enssat.fr", id: "ER1886"),
    (name: "Gabriel Ardila Vidal ", email: "@", id: "ER1824"),
    (name: "name", email: "@", id: ""),
  ),
  
  teacher : (
    name : "Adrian Wójcik, M.Sc.",
    email :"adrian.wojcik@put.poznan.pl",
  ),
  date: "Winter Semester 2024/2025",
)
#set par(first-line-indent: 1em)

= Introduction

#h(1em) In this experiment, we will measure temperature using the SCD30 sensor, a highly accurate device designed to track temperature and humidity. To control the temperature, we will employ a heating element consisting of a resistor, which will act as the heater. The heating process will be regulated through an N-MOSFET module, which will adjust the power based on a PWM signal. This PWM signal will be calculated using a PID controller, taking into account the temperature measurements. The PID algorithm will enable precise and dynamic control of the temperature, ensuring it stays within the desired range.





The project will be versioned and maintained collaboratively on GitHub @GitHub, enabling efficient tracking of developments and optimal management of contributions.

#figure(
  caption: [#link("https://sensirion.com/products/catalog/SCD30","SCD30 sensor ")@SCD30]
)[
#image("../IMG/scd30.jpg")
]

#pagebreak()
= Structure

== Block Diagram
\
\

#figure(
  caption: [Block Diagram]
)[
#image("../IMG/blockDiagram.drawio.png")
]

== SCD30

#figure(
  caption: [SCD30 Pins]
)[
#image("../IMG/scd30Pins.jpg", width: 50%)
]
#figure(
  caption: [Temperature Specification]
)[
#image("../IMG/temparr.png")
]
Although the Sensirion sensor module offers additional capabilities, such as CO2 detection and humidity monitoring, our primary focus will be on utilizing its temperature sensing feature. While the integrated sensor excels at providing accurate readings of CO2 levels and humidity, for this application, we will concentrate on leveraging its precise temperature measurement capabilities to control and monitor the temperature. This allows us to take advantage of the sensor's advanced technology while prioritizing temperature regulation for our specific needs.

The library to control this sensor is available on this git : @GitHubSCD

== N-MOSFET module

#figure(
  caption: [N-MOSFET module]
)[
#image("../IMG/mosfet.jpg", width: 50%)
]

#figure(
  caption: [N-MOSFET module pin]
)[
#image("../IMG/pinMosf.jpg", width: 50%)
]
== Circuit
#figure(
  caption: [Circuit]
)[
#image("../IMG/circuitSys.png")
]
The diagram circuit above is based on the transistor as switch circuit with a unipolar N-channel transistor
 (NMOS). System power supply voltage is 5V. The transistor switch is controlled by the PWM signal
 from the selected timer channel (Timer 1, channel 1).
 There is an I2C communication with the sensor for transmitting the temperature measurements.
 The Pwm calculation is based on temperature measurement and a PI controller. 


#pagebreak()
#bibliography("ref.yml")
