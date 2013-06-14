#!/usr/bin/python
#				 -*- mode: python; coding: utf-8 -*-
#
# Affichage de l'environnement
#
#           Author: Erick Gallesio [eg@unice.fr]
#    Creation date: 28-Dec-2008 11:58 (eg)
# Last file update:  2-Jun-2013 12:05 (eg)


from os import *
from cgi import escape

# Le header
print("Content-type: text/html; charset=utf-8")
print("")

# Le contenu de la page
print("<html><head><title>Variables CGI</title></head><body>")
print("<h2>Liste des variables d'environnement</h2>")

print("<pre><table>")
for var in sorted(environ):
    print("<tr >")
    print("<td style='border:0px; text-align:right'> %s = </td>" % escape(var))
    print("<td style='border:0px' > %s </td>" % escape(environ[var]))
    print("</tr>")
print("</pre></table>")

print("<b>Repertoire courant: </b>%s\n" % getcwd())
print("</body></html>")
