#!/usr/bin/perl 

use File::Spec;

$pythonScript = $ARGV[0];
$ENV{'Path'}=$ENV{'DIR_PYTHON'};

sub PerlCallPython
{
    my $path_curf = File::Spec->rel2abs(__FILE__);
    #print "C PATH = ",$path_curf,"\n";
    my ($vol, $dirs, $file) = File::Spec->splitpath($path_curf);
    #print "C Dir = ", $dirs,"\n";
    chdir $dirs;
    system("python $pythonScript");
}

PerlCallPython();