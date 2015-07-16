#!/usr/bin/perl -w
use utf8;
use CGI;                             # load CGI routines
$q = CGI->new;                        # create new CGI object
print $q->header,                    # create the HTTP header
        $q->start_html('Activa / desactiva la electrovàlvula'); # start the HTML
# Actua segons el paràmetre accio
if ($q->param('accio') eq 'ACTIVA') {
        print $q->h1('Electrovàlvula activada');         # level 1 header
        open(SORTIDA, ">/tmp/existeixo.flag");
        print SORTIDA "YESSSSS";
        close SORTIDA;
} elsif ($q->param('accio') eq 'DESACTIVA') {
        print $q->h1('Electrovàlvula DESactivada');         # level 1 header
        unlink "/tmp/existeixo.flag";
} else {
        print $q->h1('Consulta a la electrovàlvula');
}
$activada = (-e "/tmp/existeixo.flag"?'activada':'desactivada');

# round robin database creada amb la comanda :
# rrdtool create /var/local/nivell.rrd DS:nivell:GAUGE:600:U:U RRA:AVERAGE:0.5:6:10
## Les bases de dades rrd, es caracteritzen perque guarden dades una cada interval de temps
## esborrant les que queden antigues. Ideal per conservar informació de sensors
$sortida = `rrdtool lastupdate /var/local/nivell.rrd`; # comanda de shell que retorna la darrera dada introduida
@parts = split(':',$sortida);   # parteix la cadena de sortida perquè
$nivell = $parts[1];            # la segona part sigui la dada de nivell

print <<END;
<p>El darrer nivell passat és <b>$nivell</b> i la electrovàlvula es troba $activada</p>
<p>Per passar el nivell cal especificar-lo com
 paràmetre en el query de la crida a existeix.pl
 amb nom de paràmetre 'nivell'. Per exemple :<br />
http://$ENV{HTTP_HOST}/cgi-bin/existeix.pl?nivell=65
</p>
<p>
        <a href="?accio=ACTIVA">Activa la electrovàlvula</a>
<br />
        <a href="?accio=DESACTIVA">Desactiva la electrovàlvula</a>
</p>
END

print $q->end_html;                  # end the HTML

