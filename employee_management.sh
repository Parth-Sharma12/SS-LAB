while true
do
	echo "Enter 1 to Add a record"
	echo "Enter 2 to Delete a record"
	echo "Enter 3 to search for a record"
	echo "Enter 4 to  display record of an employee"
	echo "Enter 5 to sort"
	echo "Enter 6 to diplay the whole content"
	echo "Enter 7 to exit "

	read var
	case $var in
	"1") echo "Enter name"
	read var
     	echo "Enter age"
	read var1
	echo "Enter Department"
	read var2
	echo $var $var1 $var2 >>file.txt;;

	"2") echo "Enter serial no. of employee"
	read var
	sed 'vard' file.txt> file.txt;;
	"3") echo "Enter name to search"
	read var
	grep "$var" file.txt;;
	"4") echo "Enter Employee name whose record is to be displayed"
	read var
	grep "$var" file.txt > file.txt;;
	"5") sort file.txt;;
	"6") cat file.txt;;
	"7") exit;;
	esac
done
