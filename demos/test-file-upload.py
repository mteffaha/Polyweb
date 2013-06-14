#!/usr/bin/python
#					-*-coding: utf-8 -*-
#
# test-file-upload.py	-- Un exmple de chargement de fichier
#
# Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
#
#           Author: Erick Gallesio [eg@unice.fr]
#    Creation date: 26-May-2013 22:50 (eg)
# Last file update: 27-May-2013 16:35 (eg)
#

from os import *
from cgi import FieldStorage, escape

# Le header
print("Content-type: text/html; charset=utf-8")
print("")

# Le contenu de la page
print("<html><head><title>Test formulaires CGI</title></head><body>")

form = FieldStorage()

if form.has_key("file"):
    print("Nom de fichier chez le client: <i>%s</i><br/>" % \
              (form["file"].filename))
    print("Contenu du fichier: <hr /><pre>%s<pre><hr />" % \
              (escape(form["file"].value)))
else:
    # Pas de fichier: afficher le formulaire
    print("<form method='POST' enctype='multipart/form-data'>")
    print("Nom du fichier à charger: <input type='file' name='file' /> <br />")
    print("<input type='submit' name='submit' value='Envoyer' />")
    print("</form>")


print("</body></html>")
