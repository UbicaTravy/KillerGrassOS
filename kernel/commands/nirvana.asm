check_nirvana:
    mov di, .command
    call strcmp
    jne .skip
    mov si, .spirit_text
    call print
.skip:
    ret

.command db "nirvana", 0
.spirit_text db "", 0x0D, 0x0A
          db "Load up on guns, bring your friends", 0x0D, 0x0A
          db "It's fun to lose and to pretend", 0x0D, 0x0A
          db "She's over bored and self assured", 0x0D, 0x0A
          db "Oh no, I know a dirty word", 0x0D, 0x0A
          db "", 0x0D, 0x0A
          db "Hello, hello, hello, how low?", 0x0D, 0x0A
	      db "Hello, hello, hello, how low?", 0x0D, 0x0A
	      db "Hello, hello, hello, how low?", 0x0D, 0x0A
	      db "Hello, hello, hello...", 0x0D, 0x0A
	      db "", 0x0D, 0x0A
	      db "With the lights out it's less dangerous", 0x0D, 0x0A
	      db "Here we are now, entertain us", 0x0D, 0x0A
	      db "I feel stupid and contagious", 0x0D, 0x0A
	      db "Here we are now, entertain us", 0x0D, 0x0A
	      db "A mulatto", 0x0D, 0x0A
	      db "An albino", 0x0D, 0x0A
	      db "A mosquito", 0x0D, 0x0A
	      db "My Libido", 0x0D, 0x0A
	      db "Yay! Yay! Yay! ", 0x0D, 0x0A
	      db "", 0x0D, 0x0A
	      db "I'm worse at what I do best", 0x0D, 0x0A
	      db "And for this gift I feel blessed", 0x0D, 0x0A
	      db "Our little group has always been", 0x0D, 0x0A
	      db "And always will until the end", 0x0D, 0x0A
	      db "", 0x0D, 0x0A
	      db "Hello, hello, hello, how low?", 0x0D, 0x0A
	      db "Hello, hello, hello, how low?", 0x0D, 0x0A
	      db "Hello, hello, hello, how low?", 0x0D, 0x0A
	      db "Hello, hello, hello...", 0x0D, 0x0A
	      db "", 0x0D, 0x0A
	      db "With the lights out it's less dangerous", 0x0D, 0x0A
	      db "Here we are now, entertain us", 0x0D, 0x0A
	      db "I feel stupid and contagious", 0x0D, 0x0A
	      db "Here we are now, entertain us", 0x0D, 0x0A
	      db "A mulatto", 0x0D, 0x0A
	      db "An albino", 0x0D, 0x0A
	      db "A mosquito", 0x0D, 0x0A
	      db "My Libido", 0x0D, 0x0A
	      db "Yay! Yay! Yay!", 0x0D, 0x0A
	      db "", 0x0D, 0x0A
	      db "And I forget just why I taste", 0x0D, 0x0A
	      db "Oh yeah, I guess it makes me smile", 0x0D, 0x0A
	      db "I found it hard, it's hard to find", 0x0D, 0x0A
	      db "Oh well, whatever, never mind", 0x0D, 0x0A
	      db "", 0x0D, 0x0A
	      db "hello, hello, hello, how low?", 0x0D, 0x0A
	      db "Hello, hello, hello, how low?", 0x0D, 0x0A
	      db "Hello, hello, hello, how low?", 0x0D, 0x0A
	      db "Hello, hello, hello...", 0x0D, 0x0A
	      db "", 0x0D, 0x0A
	      db "With the lights out it's less dangerous", 0x0D, 0x0A
	      db "Here we are now, entertain us", 0x0D, 0x0A
	      db "I feel stupid and contagious", 0x0D, 0x0A
	      db "Here we are now, entertain us", 0x0D, 0x0A
	      db "A mulatto", 0x0D, 0x0A
	      db "An albino", 0x0D, 0x0A
	      db "A mosquito", 0x0D, 0x0A
	      db "My Libido", 0x0D, 0x0A
	      db "", 0x0D, 0x0A
	      db "A denial... A denial...A denial...A denial...", 0x0D, 0x0A
	      db "A denial...A denial...A denial...A denial...", 0x0D, 0x0A
	      db "A denial...", 0x0D, 0x0A
          db "", 0x0D, 0x0A, 0