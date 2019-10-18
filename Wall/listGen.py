targets = "A B C D E F G H I K L M N O P Q R S T V X Y Z"
targets = targets.split(" ")
alphabet = ""
for t in targets:
    alphabet += t.lower()
print("Weaponized")
wordlist = ""
for a in alphabet:
    for b in alphabet:
        for c in alphabet:
            for d in alphabet:
                wordlist += "p{}{}{}{}.php\n".format(a, b,c,d)
print(wordlist)
