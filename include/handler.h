/*
 * handler.c	-- Serveur Web: Gestion des handlers
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 24-Apr-2013 11:54 (eg)
 * Last file update: 26-May-2013 00:22 (eg)
 */

#ifndef POLYWEB_HANDLER_H
#define POLYWEB_HANDLER_H

// Le type de handler de requêtes HTTP
typedef int (*uri_handler_t)(struct http_request *req);

// Ajouter un nouvel handler dans la liste de handlers de requêtes
// HTTP.  Le nouvel handler est ajouté au début de la liste. Par
// conséquent, l'ordre d'ajout des handlers est important: le dernier
// handler chargé, sera exécuté avant ceux qui ont été chagé
// auparavant
void handler_uri_add(uri_handler_t hdlr);


// Construit une réponse à la requêtre HTTP "req". Pour cela, on
// parcourt la liste des handlers enregistrés et on execute les
// handler déjà enregistrés (dans l'ordre inverse de leur enregistrement).
// Lorsqu'un handler s'execute, par convention, il renvoie:
//
//     - 0 si il n'a pas pu construire une réponse à la requête "req"
//     - 1 si il a construit une réponse.
// La fonction suivante exécute donc les handlers, tant qu'ils renvoient 0.
// La fonction se termine donc dès qu'un handler renvoie 1.
void handler_build_response(struct http_request *req);

#endif
