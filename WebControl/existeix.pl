#!/usr/bin/perl -w
use CGI;                             # load CGI routines
$q = CGI->new;                       # create new CGI object
print $q->header;                    # create the HTTP header
$nivell = $q->param('nivell');
$nivell += 0;
`/usr/bin/rrdupdate /var/local/nivell.rrd N:$nivell`;
if (-e "/tmp/existeixo.flag") {
        print '<text>1</text>';      # level 1 header
} else {
        print '<text>0</text>';
}

