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
    (name: "name", email: "@", id: "ERxxxx"),
    (name: "name", email: "@", id: "ERxxxx"),
  ),
  
  teacher : (
    name : "Adrian Wójcik, M.Sc.",
    email :"adrian.wojcik@put.poznan.pl",
  ),
  date: "Winter Semester 2024/2025",
)
#set par(first-line-indent: 1em)

= Introduction

#h(1em) Air quality is becoming increasingly important in modern society, both because of environmental concerns and because of the direct effects it has on our health. Poor air quality, whether polluted or contaminated, can have serious consequences for our well-being, affecting both our respiratory tracts and our immune systems. In particular, monitoring air quality not only helps to limit the risks associated with pollutants, but also to stem the spread of viruses and other pathogens, maintaining a safer, healthier environment. In this context, monitoring CO2 concentration in indoor spaces is becoming a key indicator of ambient air quality. The SCD30 sensor does just that. This sensor measures the quantity of carbon dioxide (CO2) present in the air, providing an assessment of air quality and helping to prevent associated health risks. 

To make air quality easier to understand for the user, we have also integrated an LED management system. This system will provide a clear visual indication of air quality. 

The project will be versioned and maintained collaboratively on GitHub @GitHub, enabling efficient tracking of developments and optimal management of contributions.

#figure(
  caption: [#link("https://sensirion.com/products/catalog/SCD30","SCD30 sensor ")@SCD30]
)[
#image("../IMG/scd30.jpg")
]

#pagebreak()
= Structure

== Block Diagram

== SCD30

#figure(
  caption: [SCD30 Pins]
)[
#image("../IMG/scd30Pins.jpg", width: 50%)
]

== LEDs

#figure(
  caption: [LEDs circuit]
)[
#rotate(-90deg)[#image("../IMG/LED.png", width: 60%)]
]






#pagebreak()
#bibliography("ref.yml")
