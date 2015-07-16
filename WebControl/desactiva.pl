#!/usr/bin/perl -w
use CGI;                             	# load CGI routines
$q = CGI->new;                        	# create new CGI object
print $q->header,                    	# create the HTTP header
        $q->start_html('hello world'); 	# start the HTML
print $q->h1('Desactivat');         	# level 1 header
unlink "/tmp/existeixo.flag";
print $q->end_html;                  	# end the HTML
