for d in */*;
	do (make fclean -C "$d");
done
CLEAN_COMMAND=trash
which $CLEAN_COMMAND > /dev/null || CLEAN_COMMAND=rm
find . \( -name '*.[od]' -or -name '.DS_Store' \) -exec $CLEAN_COMMAND -v {} \;
