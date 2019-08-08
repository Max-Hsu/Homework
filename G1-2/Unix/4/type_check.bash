#!/usr/bin/tcsh
cd ~/G
rm -r ~/R/* >& ~/X
rm ~/G/pokey/root/usr/toukmond/*.o >& ~/X
cd rooms
find . -name "*[12]" |xargs grep ".*" |  sed -n "/1:/p" | tr " " "-" |  sed "s/^.*:/mkdir /" > ~/R/tmpa
find . -name "*[12]" | xargs grep ".*" | sed "s/.*1://;TJ;y~ABCDEFGHIJKLMNOPQRSTUVWXYZ/ ~abcdefghijklmnopqrstuvwxyz--~;h;d;:J;/\.description/d;s/:/echo "\""/ ; G ; s/\n/"\"" >> / ; s~.*~&/description~" > ~/R/tmpb
find . -name "*[1a-z]"  | grep  -v -e "\(/[.bcdfgst][liarkw][inabostre][gscifphebltk].*"\$"\)\|\(/.\{1,2\}"\$"\)" -e "^\./[^/]*"\$"" | sed ":J;s~/\([^x]\{1,2\}\)/~/x\1/~;tJ" | sort | sed "s/x//g;/.des/s/\(.*\)/cat \1|tr A-Z\/\  a-z-/; s~^\.\/.*\/\(.*\)~echo \1.o~" > ~/R/tmp
chmod u+x ~/R/tmp; ~/R/tmp | sed "/\.o"\$"/"\!"{h;d;};x;G;h;s~\n.*~~;x;s~\n~/~;s~^~echo -n > ~" > ~/R/tmpc
ls ~/I| sed 's_.*_echo > ~/G/pokey/root/usr/toukmond/&.o_' >~/R/tmpd
cd ~/R;(chmod 777 tmp?; ./tmpa; ./tmpb; ./tmpc; ./tmpd; ) >& ~/X  #when finish add #rm tmp?
cd ~/G/pokey/root;
touch -d 1970-1-1 *;touch -d 1970-1-1 */*;touch -d 1970-1-1 */*/*
chmod 766 *;chmod 766 */*;chmod 766 */*/*
cd `cat ~/G/pwd`

while ( 1 )
	while ( 1 )
		echo -n '$ '
		set InComm = $<:q
		if ( "A$InComm" != "A" ) break
	end
	#set echo;set verbose
	set com = `echo $InComm | sed "s/ .*//"`
	set arg = `echo $InComm | sed "s/$com *//;s/ .*//"`
	echo com #added
	echo $com #added
	echo arg #added
	echo $arg #added
	#unset echo; unset verbose
	unset notHandledYet
	if ( "A$arg" == "A" ) then
		switch ( $com ) 
			case echo:
				echo; breaksw
			case cat:
				echo "Usage: cat <ascii-file-name>"; breaksw
			case uncompress:
				echo "Usage: uncompress <filename>"; breaksw      
			case ftp:
				echo "ftp: hostname required on command line."; breaksw
			case rlogin:
				echo "Usage: rlogin <hostname>"; breaksw
			case cd:
				echo "Usage: cd <path>"; breaksw
			case ls:
				set arg = "."
			default:
				set notHandledYet
		endsw
	endif
	
	if ( $?arg || $?notHandledYet ) then
	switch ( $com ) 
		case exit:
			echo
			echo You step back from the console.
			echo
			exit 1
		case echo:
			echo `echo $InComm | sed "s/^[^\ ]* //"`
			breaksw
		case pwd:
			pwd | sed 's_.*root/*_/_'
			breaksw
		case cd:
		case ls:
			pwd > ~/G/pwd
			if ( `echo $arg | sed "s/\(.\).*/\1/"` == "/" ) cd ~/G/pokey/root
			set arg = ` echo $arg | tr "/" " " ` ; foreach run ( $arg )
				(rm -f ~/G/runPWD;cd $run;pwd -P > ~/G/runPWD)
				if ( ! ( -e ~/G/runPWD ) ) then
					cd `cat ~/G/pwd`
					echo No such directory.
					breaksw
					endif
				cd $run
				pwd -P | grep "/root" || cd ~/G/pokey/root
				end
			if ( $com == cd ) breaksw
			( pwd -P | grep "/toukmond" > /dev/null ) && set verify = AAA || set verify = BBB
			ls -la --color=never | sort | sed "s/^/$verify /" | sed "/\(^AAA\|^BBB.*\.o\|^BBB.*toukmond\)/s/^[^ ]*[ ]*\([^ ]*[ ]*[^ ]*[ ]*\)[^ ]*[ ]*[^ ]*/\1toukmond restricted/;{s/^BBB*[ ]*\([^ ]*[ ]*[^ ]*[ ]*\)[^ ]*[ ]*[^ ]*/\1root     staff     /};/^[^ ]\{11\}/s/^\([^ ]\{10\}\)[^ ]/\1/;/^d.\{9\} . /s/^\(d.\{9\} \)[^ ]*[ ]*\([^ ]*[ ]*[^ ]*[ ]*\)[^ ]*/\13 \22048/;/[^\.]\.\{1\}"\$"/s/\([^ ]*[ ]*[^ ]*[ ]*[^ ]*[ ]*[^ ]*[ ]*\)[^ ]*/\1 512/"
			cd `cat ~/G/pwd`
			breaksw
		case cat:
			if ( $arg =~ */* ) then
				echo cat: only files in current directory allowed.
			else if ( -e $arg ) then
				if ( $arg == description ) then
					cat $arg
				else
					echo Ascii files only.
				endif
			else
				echo File not found.
			endif
		breaksw
		case uncompress:
			echo Uncompress command failed.
		breaksw
		case ftp:
			if ( $arg == gamma ) then
				echo ftp: host not responding.
			else
				echo ftp: Unknown host.
			endif
				breaksw
		case rlogin:
			if ( $arg == gamma ) then
				echo Host not responding.
			else if ( $arg != endgame ) then
				echo ftp: Unknown host.
			else
			if ( $1 !~ *90*90* ) break
			echo $1
			echo You have not achieved enough points to connect to endgame.
			endif
		breaksw
		default:
			echo "$com": not found.
		endsw
	endif
end