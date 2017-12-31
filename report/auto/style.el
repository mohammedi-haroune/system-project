(TeX-add-style-hook
 "style"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("babel" "french") ("geometry" "margin=2cm" "top=2cm" "left=2cm")))
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-environments-local "bash")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (TeX-run-style-hooks
    "inputenc"
    "babel"
    "graphicx"
    "geometry"
    "xcolor"
    "listings")
   (LaTeX-add-listings-lstdefinestyles
    "Bash"))
 :latex)

