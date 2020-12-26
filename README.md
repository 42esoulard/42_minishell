# 42_minishell
A teeny tiny shell built by rturcey and esoulard.

_Includes a tester that we borrowed from sdunkel and enriched with everything we could think of!_

**A lovely simili shell with:**
  - custom prompt, 
  - executable launch with either a relative or absolute path,
  - built-in commands:
      - echo with option -n
      - cd with a relative or absolute path
      - pwd
      - export
      - unset
      - env
      - exit
  - separation of commandes with ;
  - single and double quote handling, 
  -  < , > and >> redirections
  - pipes and pipelines
  - environment variables
  - exit status of last cmd with $?
  - signal handling of ctrl-C, ctrl-D and ctrl-\ 

Written in summer 2020.
