// The project function defines how your document looks.
// It takes your content and some metadata and formats it.
// Go ahead and customize it to your liking!
#let project(
  school: "",
  faculty: "",
  institute: "",
  course_type:"",
  course: "",
  authors: (),
  teacher : (), 
  date: none, body) = {
  // Set the document's basic properties.
  set document(author: authors.map(a => a.name),
  title: school)
  set page(numbering: "1", number-align: center)
  set text(font: "New Computer Modern", lang: "en")
  show math.equation: set text(weight: 400)
  set heading(numbering: "1.1")

  // Title row.
  align(center)[
    #v(2em, weak: true),
    #block(text(weight: 700, 1.75em, school + v(0em) + text( weight: 200, 0.75em, faculty + v(0.3cm) + institute )))
    #v(3em, weak: true)
    #image("pplogo.png", width: 50%)
    //#date
    #v(3em, weak: true)
    #text(weight: 200, 1.5em,course_type + v(0em) + course)
      // Author information.
    #pad(
    top: 0.5em,
    bottom: 0.5em,
    x: 2em,
    grid(
      columns: (1fr,) * calc.min(3, authors.len()),
      gutter: 1em,
      ..authors.map(author => align(center)[
        *#author.name* \ ID : #author.id \
        #author.email \
      ]),
    ),
  )
    #v(0.5cm)
    // Teacher information.
    #pad(
    top: 0.5em,
    bottom: 0.5em,
    x: 2em,
    grid(
      columns: 1,
      gutter: 1em,
      align(start)[
        * Leaders:* \ 
        * #teacher.name* \
        #teacher.email \
      ]
    ),
  )
  #v(3em, weak: true)
  #date
  
  ]


  pagebreak()
  // Main body.
  set par(justify: true)
    // Table of contents.
  outline(depth: 3, indent: true)
  pagebreak()
  
    set page(
      header: [
      #place(dy:0.1em)[
      #image("pplogo.png", width: 10%)
    ]  
      #place(
        dy : 0.2cm,
        dx : 4.5em,
      )[
    *#course*#course_type \
    #emph[#school] #institute
    
    ]
  #line(length: 100%)
  ]
)  
  

  body
}