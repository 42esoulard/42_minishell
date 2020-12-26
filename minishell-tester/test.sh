# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell

#echo 'export TEST="   '   blabla    '    " ; TEST+=LOL ; echo $TEST ; echo "$TEST" ; env | sort | grep -v SHLVL | grep -v _= ' "; exit" | ./minishell 2>&- > ms.txt
#echo 'export TEST="   '   blabla    '    " ; TEST+=LOL ; echo $TEST ; echo "$TEST" ; env | sort | grep -v SHLVL | grep -v _= ' "; exit" | bash 2>&- > sh.txt

function exec_test()
{
	TEST1=$(echo $@ "; exit" | ./minishell 2>&-)
	#TEST1=$(echo $@ | valgrind ./minishell 2>&-)
	ES_1=$?
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓"
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

# TESTS 4-11-20
exec_test '"ls"'
exec_test '"ls" bla ;'
exec_test '        "ls"        '
exec_test '"cd"'
exec_test '"cd" bla ;'
exec_test '        "cd"        '
exec_test '";ls    ;"'
exec_test '"ls bla" ;'
exec_test '        "ls    bla"        '
exec_test '";cd       ;"'
exec_test '"cd bla" ";"'
exec_test '"cd bla ;"'
exec_test '        "cd    bla"        '
exec_test "'ls'"
exec_test "'ls' bla ;"
exec_test "        'ls'        "
exec_test "'cd'"
exec_test "'cd' bla ;"
exec_test "        'cd'        "
exec_test "'ls    ;'"
exec_test "'ls bla '';'"
exec_test "        'ls bla'        "
exec_test "'cd      ;'"
exec_test "'cd bla '';'"
exec_test "'cd bla ;'"
exec_test "        'cd bla'        "

# ECHO TESTS
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'


# CD TESTS
exec_test 'cd .. ; pwd'
exec_test 'cd /Users ; pwd'
exec_test 'cd ; pwd'
exec_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'


# PIPE TESTS
exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
exec_test 'cat /dev/random | head -c 10 | wc -c'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'

# ENV EXPANSIONS + ESCAPE
exec_test 'echo test     \    test'
exec_test 'echo \"test'
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo test "" test "" test'
exec_test 'echo "\$TEST"'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$?TEST"'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$1TEST"'
exec_test 'echo "$T1TEST"'

# ENV EXPANSIONS
ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
exec_test 'export ='
exec_test 'export 1TEST= ;' $ENV_SHOW
exec_test 'export TEST ;' $EXPORT_SHOW
exec_test 'export ""="" ; ' $ENV_SHOW
exec_test 'export TES=T="" ;' $ENV_SHOW
exec_test 'export TE+S=T="" ;' $ENV_SHOW
exec_test 'export TEST=LOL ; echo $TEST ;' $ENV_SHOW
exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
exec_test 'export TEST=LOL; export TEST+=LOL ; echo $TEST ;' $ENV_SHOW
exec_test $ENV_SHOW
exec_test $EXPORT_SHOW
exec_test 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; ' $ENV_SHOW

# REDIRECTIONS
exec_test 'echo test > ls ; cat ls'
exec_test 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'
exec_test '> lol echo test lol; cat lol'
exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'

# MULTI TESTS
exec_test 'echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem'

# SYNTAX ERROR
exec_test ';; test'
exec_test '    ;;test'
exec_test 'test               ; ; ; ;'
exec_test 'echo | ls;;'
exec_test 'echo | ls;;       '
exec_test 'echo ; ls |        ; ls;;'
exec_test 'echo ; exit |        ; ls;;'
exec_test 'echo ; exit ;;'
exec_test 'echo ; exit ;|;'
exec_test 'ec;h|o ; ls |; ls;;'
exec_test '| test'
exec_test 'echo > <'
exec_test 'echo | |'
exec_test '<'

# EXIT
exec_test "exit 42"
exec_test "exit 42 53 68"
exec_test "exit 259"
exec_test "exit 9223372036854775807"
exec_test "exit -9223372036854775808"
exec_test "exit 9223372036854775808"
exec_test "exit -9223372036854775810"
exec_test "exit -4"
exec_test "exit wrong"
exec_test "exit wrong_command"
exec_test "gdagadgag"
exec_test "ls -Z"
exec_test "cd gdhahahad"
exec_test "ls -la | wtf"

# BERZEK
exec_test 'export test="    '      test    '      " ; echo $test ; echo "$test" ; ' $ENV_SHOW
exec_test 'export test="ls -la ; echo test" ; $test ; echo "$test" ; ' $ENV_SHOW
exec_test 'export TEST="   '   blabla    '    " ; TEST+=LOL ; echo $TEST ; echo "$TEST" ; ' $ENV_SHOW
exec_test 'export TEST="   '   test1    '    " ; TEST+="   '   test2    '    " ; echo $TEST ; echo "$TEST" ; ' $ENV_SHOW
rm lol ls test


#7-10-20-PROBLEMES
exec_test "echo<bullshit "
exec_test "<bullshit echo"
exec_test "<bullshit"
exec_test "<bullshit ls"
exec_test "ls <bullshit"
exec_test "echo>unauthorized       ; echo<unauthorized"
exec_test "$VAR_QUI_NEXISTE_PAS"
exec_test "export VAR_VIDE;$VAR_VIDE; export VAR_BLA=ABCDE; VAR_VIDE+=$VAR_BLA; VAR_VIDE+=fghij bla; bla; echo $VAR_VIDE; VAR_VIDE=''; echo $VAR_VIDE;"
exec_test "export (zeryut=ptdr"
exec_test "Makefile"

#17-10-TO-FIX
exec_test 'export pouet="echo coucou" ; $pouet'
exec_test 'export pouet="e""cho"' coucou' ; $pouet'
exec_test 'export test="   a   "'
exec_test 'echo $test'
exec_test 'echo $test$test$test$test$test$test$test$test$test$test$test'
exec_test 'echo "$test$test$test$test$test$test$test$test$test"'
exec_test 'echo test | exit'
exec_test 'exit | echo test'
exec_test 'exit 165411651651615132132 | echo test'
exec_test 'exit asdas | echo test'
exec_test 'exit 1 2 3 | echo test'

exec_test 'echo test| exit'
exec_test 'echo test| exit 165411651651615132132'
exec_test 'echo test | exit asdas'
exec_test 'echo test | exit 1 2 3'
exec_test 'echo test | exit 1 a 2 3'
exec_test 'cd pouet ; exit ;'

#TESTS_A_FAIRE.txt
exec_test 'mkdir repo; ./minishell<repo'
exec_test 'mkdir unauthorized; chmod 000 unauthorized; cd unauthorized; ls>unauthorized; ls<unauthorized'
exec_test '<bullshit'
exec_test '<bullshit ls'
exec_test '<bulshit echo'
exec_test 'cd | ls | cat  '
exec_test 'mkdir a; cd a; rm -r ../a; cd . ; cd.; cd .; cd ..; cd .. ; cd .'
exec_test 'mkdir a; cd a; mkdir b; cd b; rm -r ../../a; cd . ; cd.; cd .; cd ..; cd .; cd .. ; cd .'
exec_test 'mkdir unauthorized; chmod 000 unauthorized; cd unauthorized; ls>unauthorized; ls<unauthorized; echo>unauthorized       ; echo<unauthorized ; chmod 777 unauthorized; rm -r unauthorized'
exec_test 'bullshit<<<<<<<>>>>l | bullshi'
exec_test '<bullshit'
exec_test '<bullshit ls'
exec_test '<bullshit echo'
exec_test 'cd . | bullshit'
exec_test 'cd .. | bullshit'
exec_test 'bullshit | cd .'
exec_test 'bullshit | cd ..'
exec_test 'touch norights; chmod 000 norights   ;echo bonjour > lol > norights'
exec_test '../sources/pipes.c'

#TESTS_ALIEN
#ECHO
exec_test 'pwd;cd libft;pwd;cd ..;pwd'
exec_test 'echo coucou'
exec_test 'echo -n coucou'
exec_test 'echo "coucou"'
exec_test 'echo -n "coucou"'
exec_test 'echo "coucou" "bonjour"'
exec_test 'echo 'coucou' bonjour'
exec_test 'echo'
exec_test 'echo -nabc coucou'
exec_test 'echo -n -n coucou'
exec_test 'echo -nnnnn -nnn-nab coucou'

#ENV
exec_test 'env | grep PATH'
exec_test 'env | grep SHLVL'

#EXPORT
exec_test 'export coucou=salut ; env | grep coucou ; unset coucou'
exec_test 'export cou=ec ; export bon=ho ; $cou$bon salut'
exec_test 'export cou=ec ; export bon=ho ; "$cou$bon" salut'
exec_test 'export cou=ec ; export bon=ho ; '$cou$bon' salut'
exec_test 'export cou=ec ; export bon=ho ; \$cou\$bon salut'
exec_test 'export cou=ec ; export bon=ho ; \'$cou$bon\' salut''
exec_test 'export cou=ec ; export bon=ho ; \"$cou$bon\" salut'
exec_test 'export cou=ec ; export bon=ho ; "\$cou\$bon" salut'
exec_test 'export cou=ec ; export bon=ho ; '\$cou\$bon' salut'
exec_test 'export cou=ec ; export bon=ho ; $cou $bon salut'
exec_test 'export cou=ec ; export bon=ho ; "$cou $bon" salut'
exec_test 'export cou=ec ; export bon=ho ; $cou\ $bon salut'
exec_test 'export cou=ec ; export bon=ho ; "$cou\ $bon" salut'
exec_test 'export pouet="echo coucou" ; $pouet'
exec_test 'export pouet="e""cho"' coucou' ; $pouet'
exec_test 'export test="   a   " ; echo $test;echo $test$test$test$test$test$test$test$test$test$test$test;echo "$test$test$test$test$test$test$test$test$test";unset test'
exec_test 'export TEST=coucou; export TEST+=bonjour ;export | grep TEST ;unset TEST'
exec_test 'export TE+S=T="" ; env | sort | grep -v SHLVL | grep -v _= | grep TEST'
exec_test 'export TEST=LOL; export TEST+=LOL ; echo $TEST ; env | sort | grep -v SHLVL | grep -v _= | grep TEST ; unset TEST'
exec_test 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ;  env | sort | grep -v SHLVL | grep -v _= | grep TEST ; unset TEST'
exec_test 'export test=hello ; export test ; env | grep test | grep -v alien; unset test'
exec_test 'export test=hello ; export test += coucou ; env | grep test | grep -v alien ; unset test'
exec_test 'export TEST ; export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD'

#LS
exec_test 'ls'
exec_test 'ls -la'
exec_test '/bin/ls'
exec_test '../../../../../../../../../../../../bin/ls'
exec_test '../../../../../bin/ls'
exec_test '../../../../bin/ls'
exec_test '../../../bin/ls'
exec_test '../../bin/ls'
exec_test '/bin/../bin/../bin/ls'

#PARSING
exec_test 'echo \	\	coucou1'
exec_test 'echo \		coucou2'
exec_test 'echo		coucou3'
exec_test 'echo    coucou4	\	\    '
exec_test 'echo    coucou5\	\	\   ' 
exec_test 'echo     coucou6     	'
exec_test 'echo    coucou7	"	""    "'
exec_test 'echo    coucou8"	""	""    "'
exec_test 'echo "	""	"coucou9'
exec_test 'echo "	""	"coucou10'
exec_test 'echo    coucou11	'	''    ''
exec_test 'echo    coucou12'	''	''    ''
exec_test 'echo '	''	'coucou13'
exec_test 'echo '	''	'coucou14'
exec_test 'echo coucou\	    \	coucou15'
exec_test 'echo coucou\	    	coucou16'
exec_test 'echo coucou	    	coucou17'
exec_test 'echo    coucou	\	\    coucou18'
exec_test 'echo    coucou\	\	\    coucou19'
exec_test 'echo    coucou     	coucou20'
exec_test 'echo'
exec_test 'echo $'PWD''
exec_test 'echo $"PWD"'
exec_test 'echo $'RIP''
exec_test 'echo $"RIP"'
exec_test 'echo $3'
exec_test 'echo $324'
exec_test 'echo $RIP'
exec_test '$3'
exec_test '$324'
exec_test '$RIP'
exec_test '$LS'
exec_test '$R1I2P3'
exec_test '$1R2I3P'
exec_test 'echo $ '
exec_test 'echo'
exec_test 'echo "--bkslh--"'
exec_test 'echo \$'PWD''
exec_test 'echo \$"PWD"'
exec_test 'echo \$'RIP''
exec_test 'echo \$"RIP"'
exec_test 'echo \$3'
exec_test 'echo \$324'
exec_test 'echo \$RIP'
exec_test 'echo \$ '
exec_test 'echo'
exec_test 'echo "$'PWD'"'
exec_test 'echo "$'PWD'"'
exec_test 'echo "$'RIP'"'
exec_test 'echo "$'RIP'"'
exec_test 'echo "$3"'
exec_test 'echo "$324"'
exec_test 'echo "$RIP"'
exec_test 'echo "$ "'
exec_test 'echo'
exec_test 'echo '$"PWD"''
exec_test 'echo '$"PWD"''
exec_test 'echo '$"RIP"''
exec_test 'echo '$"RIP"''
exec_test 'echo '$3''
exec_test 'echo '$324''
exec_test 'echo '$RIP''
exec_test 'echo '$ ''
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$?TEST"'
exec_test 'echo "$1TEST"'
exec_test 'echo "$9TEST"'
exec_test 'echo "$T1TEST"'
exec_test 'echo "coucouc;"'
exec_test 'echo -n -n One"argument"'lo'l; echo n'
exec_test 'echo -n -n One"argument"'lo'l; echo "n"'
exec_test '"echo -n -n One"argument"'lo'l; echo "n"''ee"d"more'\?'"''""'''
exec_test 'echo -n One"argument"'lo'l ; echo "n"''ee"d"more'?'''""'
exec_test 'echo -n -n return'
exec_test 'echo test "" test "" test'
exec_test 'ls |'
exec_test 'ls'
exec_test 'ls >'


#backslash
exec_test 'echo 1 "coucou\"bonjour"'
exec_test 'echo -n "8	 \l\s"'
exec_test 'echo -n "9	\ \l\s"'
exec_test "echo 11 \'coucou"
exec_test 'echo -n "12	echo \-n coucou"'
exec_test 'echo -n "13	echo\ -n coucou"'
exec_test 'echo '\\please\\' "\"fail\\"'

#CAT
exec_test 'cat Makefile'
exec_test 'cat -e Makefile'

#PIPES
exec_test 'echo test | | wc; echo lol'
exec_test 'echo | echo coucou'
exec_test 'echo | echo coucou | cat -e'
exec_test 'ls | echo coucou'
exec_test 'echo coucou | ls'
exec_test 'ls | cat -e'
exec_test 'ls | sort'
exec_test 'ls | grep .sh'
exec_test 'ls | grep .sh | sort'
exec_test 'ls | grep .sh | sort | cat -e'
exec_test 'ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls '
exec_test 'ls | grep j | cat -e | echo coucou ; pwd ; env | grep coucou'
exec_test 'cat test.sh | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat'

#PWD
exec_test 'pwd'
exec_test 'pwd salut'

#QUOTES
exec_test 'echo "coucou"'
exec_test 'echo "coucou\""'
exec_test 'echo "coucou" "salut"'
exec_test 'echo "\$"'
exec_test 'echo "$"'
exec_test 'echo $'
exec_test 'echo \\$'
exec_test 'echo \\\$'
exec_test "echo 'coucou'"
exec_test "echo 'coucou\'"
exec_test "echo 'coucou' 'salut'"
exec_test "echo '\$'"
exec_test "echo '$'"

#>
exec_test 'ls > 0test.log;sort < 0test.log ;grep .sh < 0test.log;rm 0test.log'
exec_test 'echo bonjour.sh >> 0test.log;echo salut.sh >> 0test.log;echo hello.sh >> 0test.log;sort < 0test.log;grep .sh < 0test.log;rm 0test.log'
exec_test 'sort < 0test.log'
exec_test 'echo coucou > test.log;ls;cat test.log;rm test.log'
exec_test 'echo coucou > test.log\ coucou;ls;cat test.log\ coucou;rm test.log\ coucou'
exec_test 'echo coucou > 0test.log > 1test.log;ls;cat 0test.log;cat 1test.log;rm 0test.log 1test.log'
exec_test 'ls > test.log;ls;cat test.log;rm test.log'
exec_test 'ls > 0test.log\ coucou;ls;cat 0test.log\ coucou;rm 0test.log\ coucou'
exec_test 'ls > 1test.log\ coucou;ls;cat 1test.log\\\ coucou;rm 1test.log\ coucou'
exec_test 'ls > 2test.log > 3test.log;ls;cat 2test.log;cat 3test.log;rm 2test.log 3test.log'
exec_test 'export | grep SHELL > 0test.log;cat 0test.log;rm 0test.log'
exec_test 'env | SHELL > 0test.log;cat 0test.log;rm 0test.log'
exec_test 'pwd > 0test.log;cat 0test.log;rm 0test.log'
exec_test 'cd srcs > 0test.log;cd ..;cat 0test.log;rm 0test.log'
exec_test 'echo coucou> test.log;ls;cat test.log;rm test.log'
exec_test 'echo coucou >test.log;ls;cat test.log;rm test.log'
exec_test 'echo coucou>test.log;ls;cat test.log;rm test.log'

#>>
exec_test 'echo 1 coucou >> test0.log\ coucou; ls ;cat test0.log\ coucou;rm test0.log\ coucou'
exec_test 'echo 4; ls >> 0test.log\ coucou ;ls;cat 0test.log\ coucou;rm 0test.log\ coucou'
exec_test 'echo 5;ls >> 1test.log\ coucou;ls;cat 1test.log\\\ coucou;rm 1test.log\ coucou'
exec_test 'echo 6 ; ls >> 2test.log >> test0.log;ls;cat 2test.log;cat test0.log;rm 2test.log; rm test0.log'

#G_ERR
exec_test 'echo $?;echo coucou;echo $?'
exec_test 'ls lishdzfgl ;echo $?'
exec_test 'exit 1 2 ;echo $?'
exec_test 'exit 1 2 |echo $?'
exec_test 'exit 1 2 ;echo bla; echo $?'
exec_test 'exit qljdlkqsdjlqksdj ; echo $?'
exec_test 'exit qljdlkqsdjlqksdj | echo $?'
exec_test 'sdffs;echo $?'

# ;
exec_test 'ls ; ls ; ls'
exec_test 'ls ; pwd'

#UNSET
exec_test 'export coucou=salut;env | grep coucou ;unset coucou;env | grep coucou'
exec_test 'unset PATH; ls; exit'


#EXCEL
exec_test ';'
exec_test '/bin/echo "test";/bin/ls / '
exec_test '/bin/echo "test" ;/bin/ls / '
exec_test '/bin/echo "test"; /bin/ls / '
exec_test '/bin/echo "test" ; /bin/ls / '
exec_test "/bin/ls"
exec_test "/bin/ls fichiernul"
exec_test "/bin/echo message cool"
exec_test "/bin/echo bonjour | grep bon"
exec_test "/bin/echo petit papillon | cat"
exec_test '/bin/echo "" | cat -e'
exec_test '/bin/echo "" "test" | cat -e'
exec_test '/bin/echo "\""'
exec_test '/bin/echo "\"" | cat -e'
exec_test '/bin/echo " ; ceci est      un test" "$PWD" | cat -e'
exec_test '/bin/echo "\"\"\"\"\"\"\"\"\"\"\"\"\"" | cat -e'
#multiline
#exec_test '/bin/echo "\"\"\"\"\"\"\"\"\"\"\"\"\"\" | cat -e'

exec_test "/bin/echo '' | cat -e"
exec_test "/bin/echo '' 'test' | cat -e"
exec_test "/bin/echo '\'"
#multiline
#exec_test "/bin/echo '\'' | cat -e"
#exec_test "/bin/echo '\'\'\'\'\'\'\'\'\'\'\'\'\'' | cat -e"

exec_test "/bin/echo ' ; ceci est      un test' '$PWD' | cat -e"
exec_test "/bin/echo '\'\'\'\'\'\'\'\'\'\'\'\'\'\' | cat -e"
exec_test 'cd /; bin/ls'
exec_test 'cd /bin ; ./echo youpi'
exec_test 'cd / ;bin/../bin/../bin/../bin/../bin/../bin/../bin/../bin/../bin/../bin/echo'
exec_test 'cd ; ../../../../../../../../../../../../../../../../../../../../../../../../bin/ls'

exec_test 'ls; echo ceci n’est pas un test | wc'
exec_test 'unset PATH; ls; echo ceci n’est pas un test | wc'
exec_test 'echo trop bien > fichierbien; cat fichierbien'
exec_test 'echo Hello World | grep llo '
exec_test 'ls fichiernul | grep bla | more'
exec_test 'echo more texte > fichiertxt; cat fichiertxt'
exec_test 'rm fichiertxt; echo more texte > fichiertxt; echo more texte >> fichiertxt; cat fichiertxt'
exec_test 'rm fichierbien fichiertxt file'

exec_test 'cd .'
exec_test 'cd ..'
exec_test 'cd; cd Documents'
exec_test 'cd /caexistepas'
exec_test 'cd test test2'

exec_test 'echo test'
exec_test 'echo'
exec_test 'echo -n test'
exec_test 'echo $TEST'
exec_test 'echo -nab'
exec_test 'echo -n -n -n -n'
exec_test 'echo -nnnnn'
exec_test 'echo -nnnnn -nnnn -nn'
exec_test 'echo -nop -nn -nnnn'
exec_test 'echo -n -nope -nnnn'

exec_test 'exit'
exec_test 'exit 22'
exec_test 'exit 36 45'
exec_test 'exit -65'
exec_test 'exit allo'
exec_test 'exit 12 bonjour'
exec_test 'exit bonjour 8'
exec_test 'exit 12121212121212121212121212'

exec_test 'export TEST=oui ;' $ENV_SHOW
exec_test 'export TEST=nan ;' $ENV_SHOW
exec_test 'export bon= ;' $ENV_SHOW
exec_test 'export youpi ;' $EXPORT_SHOW
exec_test 'export _azerty ;' $EXPORT_SHOW
exec_test 'export qwerty_' $EXPORT_SHOW
exec_test 'export wow2 ;' $EXPORT_SHOW
exec_test 'export 3kliksphilip ;' $EXPORT_SHOW
exec_test 'export (zeryut=ptdr ;' $EXPORT_SHOW

exec_test 'pwd arg'
exec_test 'pwd 1234 arg'
exec_test 'pwd qlkdjqlskdj lkj qsdlkj qsdlkjqds l1234 arg'
exec_test 'pwd .'
exec_test 'pwd ..'
exec_test 'export _oui; unset _oui ;' $EXPORT_SHOW
exec_test 'export non;unset non ;' $EXPORT_SHOW
exec_test 'unset 2jour ;' $EXPORT_SHOW
exec_test 'unset bien ;' $EXPORT_SHOW
exec_test 'rm -rf 0test.log lol norights repo'




#--------------------------------------------------------#
#tests à la main, faire les commandes groupées à la suite

#env -i ./minishell
#env
#unset [TOUTES LES VAR]
#env
#env -i bash
#env
#unset [TOUTES LES VAR]
#env

#unset PATH
#env
#ls
#echo
#unset [PREMIER ELEM DE L'ENV]
#env
#unset [DERNIER ELEM DE L'ENV]
#env

#ls
#cat

#lol'"

#opera | bullshit

#cat | cat | ls

#bul ;; su; ;|opera

#bullshit | opera

#bullshit | opera |  cd

#ls | ./minishell

# exit 1 2
# [check in VM if exits or no (exits in 3.2, does not in 5.0)]
# echo $?

#blablabal
#[ENTER SEVERAL TIMES]
#$?

#Test d'ajout de dossier à PATH que j'ai tjs pas compris

#Check fermeture des fds avec ls -la /proc/$$/fd


#----------- SIGNALS -----------
#on an empty line
#^C [and ENTER]
#^C [and write something after and ENTER]
#^D
#^C ^D
#^C [and ENTER] ^D
#^C [and write something after and ENTER] ^D
#^C ^\ [and write something after and ENTER]
#^C ^C ^D
#^\ ^C ^D
#^\ [and write something after and ENTER]
#^\ [and ENTER]

#on a started line
#^C [and ENTER]
#^C [and write something after and ENTER]
#^D [and ENTER]
#^D [and write something after and ENTER]
#^C ^D
#^C [and ENTER] ^D
#^C [and write something after and ENTER] ^D
#^C ^\ [and write something after and ENTER]
#^C ^C ^D
#^\ ^C ^D
#^\ [and write something after and ENTER]
#^\ [and ENTER]

#during a cat
#^C [and ENTER]
#^C [and write something after and ENTER]
#^D [and ENTER]
#^D [and write something after and ENTER]
#^C ^D
#^C [and ENTER] ^D
#^C [and write something after and ENTER] ^D
#^C ^\ [and write something after and ENTER]
#^C ^C ^D
#^\ ^C ^D
#^\ [and write something after and ENTER]
#^\ [and ENTER]

#during opera
#during a cat
#^C [and ENTER]
#^C [and write something after and ENTER]
#^D [and ENTER]
#^D [and write something after and ENTER]
#^C ^D
#^C [and ENTER] ^D
#^C [and write something after and ENTER] ^D
#^C ^\ [and write something after and ENTER]
#^C ^C ^D
#^\ ^C ^D
#^\ [and write something after and ENTER]
#^\ [and ENTER]

#----------- END OF SIGNALS -----------


#make leaks


#MAKEFILE
#>>>> Que les includes soit bien listés

