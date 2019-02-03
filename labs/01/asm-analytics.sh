objdump -d ./simple_foo > output.txt

declare -A instructions
declare -A functions

COUNTER=0
MATCHES=0
INFUNCTION=false
while read line; do
    if [[ $INFUNCTION == true ]]; then
        if [[ -z $line ]]; then
            INFUNCTION=false
        else
            set $line
            ACTIONREAD=false
            for word in $line; do
                if [[ $ACTIONREAD == false ]] && [[ $word =~ ^[a-z][a-z][a-z][a-z]*$ ]] || [[ $word == "je" ]]; then
                    instructions[$word]=$((instructions[$word] + 1))
                    ACTIONREAD=true
                    COUNTER=$((COUNTER + 1))
                fi
            done
        fi
    elif [[ $line =~ ^[a-z0-9].*:$ ]]; then
        ADDRESS="${line:0:16}"
        FUNCTION="${line:18:-2}"

        functions[$FUNCTION]=$ADDRESS
        
        INFUNCTION=true

        MATCHES=$((MATCHES + 1))
    fi    
done < output.txt

printf "You have %d kind of instructions in this object file:\n" "$COUNTER"
for instruction in "${!instructions[@]}"; do
    printf "\t%-6s\t: Executed %3s times\n" "$instruction" "${instructions[$instruction]}" 
done

printf "You have %d functions:\n" "$MATCHES"
for function in "${!functions[@]}"; do
    printf "\t%-21s\t: Located at %s addr\n" "$function" "${functions[$function]}" 
done
