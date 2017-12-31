(TeX-add-style-hook
 "rapport"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "•")))
   (TeX-run-style-hooks
    "latex2e"
    "front_page"
    "answer1"
    "answer2"
    "answer3"
    "answer4"
    "answer5"
    "article"
    "art10"
    "style"))
 :latex)

