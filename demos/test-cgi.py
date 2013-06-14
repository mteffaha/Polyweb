#!/usr/bin/python
#					-*-coding: utf-8 -*-
#
# test-cgi.py	-- Un programme de test de scripts CGI
#
#           Author: Erick Gallesio [eg@unice.fr]
#    Creation date: 21-May-2013 19:09 (eg)
# Last file update:  2-Jun-2013 12:12 (eg)
#

from os import *
from cgi import escape, FieldStorage

# Le header
print("Content-type: text/html; charset=utf-8")
print("")

# Le contenu de la page
print("<html><head><title>Test formulaires CGI</title></head><body>")

form = FieldStorage()

if "login" not in form or "passwd" not in form:
    # On a pas de login/passwd afficher un formulaire
    print("Entrez un login et un mot de passe dans un des  formulaires "
          "ci-dessous:")
    print("<hr>")
    print("<form method=GET>"
          "<table>"
          "<tr><td><label for='login'>Login: </label></td>"
          "<td><input type=text name='login' /> </td></tr>"
          "<tr><td><label for='passwd'>Password: </label></td>"
          "<td><input type=password name='passwd' /> </td></tr>"
          "</table>"
          "<input type=submit value='GET'>"
          "</form>")
    print("<hr>")
    print("<form method=POST>"
          "<table>"
          "<tr><td><label for='login'>Login: </label></td>"
          "<td><input type=text name='login' /> </td></tr>"
          "<tr><td><label for='passwd'>Password: </label></td>"
          "<td><input type=password name='passwd' /> </td></tr>"
          "</table>"
          "<input type=submit value='POST'>"
          "</form>")


else:
    # Ok: on affiche ce que l'on sait
    print("Valeurs saisies (méthode %s): '<b>%s</b>' et '<b>%s</b>'\n" % \
              (environ["REQUEST_METHOD"], form["login"].value,
               form["passwd"].value))

print("</body></html>")
