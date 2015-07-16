#!/usr/bin/perl -w
use CGI;                             	# load CGI routines
$q = CGI->new;                        	# create new CGI object
print $q->header,                    	# create the HTTP header
        $q->start_html('hello world'); 	# start the HTML
print $q->h1('Activat');         	# level 1 header
open(SORTIDA, ">/tmp/existeixo.flag");
print SORTIDA "YESSSSS";
close SORTIDA;
print $q->end_html;                  	# end the HTML

