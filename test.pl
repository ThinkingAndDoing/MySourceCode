#!/usr/local/bin/perl
open(MYFILE,">env.txt");

$ENV{'Path'}='C:\Windows\System32';

foreach $field (keys(%ENV))
{ 
 print MYFILE "\n\n";
 print MYFILE "$field\n";
 print MYFILE "$ENV{$field}\n";
 print MYFILE "\n\n";
}

close(MYFILE);
