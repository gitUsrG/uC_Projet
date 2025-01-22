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

= Introduction


