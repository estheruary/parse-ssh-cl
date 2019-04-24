# SSH Command Line Parser

## What.

This program is called exactly like the `ssh` binary from OpenSSH, except
instead of opening a remote shell it will print the username (if specified),
host, port (if specified), and command (if specified) given on the command line.

```bash
./parse-ssh-cl -J bastion -X estelle@myhost:1234
User: estelle
Host: myhost
Port: 1234
Command:

./parse-ssh-cl -4 -q -L 8080:localhost:8080 app@prod
User: app
Host: prod
Port:
Command:

./parse-ssh-cl ssh://dev
User:
Host: dev
Port:
Command:

./parse-ssh-cl host ls -l
User:
Host: host
Port:
Command: ls -l
```

## Why?

Because when I use tmux I want to be able to open a shell on a remote host and
have the window title show the host I'm connected to. Something that can take an
SSH command line string and output the host is an important piece of that
puzzle.

## How?

* I looked at the source of OpenSSH (`ssh.c`) and saw two functions
  `parse_ssh_uri` and `parse_user_host_port` that seemed like they did what I
  wanted so I just copied them over and tried to compile them standalone.
  
* GCC yelled at me about all these missing function definitions so I copied
  them from around the code base (mostly `misc.c`).
  
* If the function wasn't there I Googled around to find out what random header I
  needed.
  
* I unearthed some heated drama surrounding `strlcpy` so I decided to copy the
  implementation from OpenBSD inline rather than link against libbsd.

* I found [greymd/ssh_opt_parse](https://github.com/greymd/ssh_opt_parse) which
  is honestly better than this project in every conceivable way.

* I copied the `getopt` string so that I could ignore all of the options, ran my
  two functions that now work, and boom, command line parsing just how upstream
  does it.

## Do.

Are you sure you really want to use this thing? Just run `make` in the source
directory and then do whatever with the `parse-ssh-cl` binary it spits out.

As far as dependencies go just about any distribution's development tools should
be more than enough to build and use. It pretty just uses libc.

How do you actually use it in your shell? Anyone who is this deep in shell
customization uses ZSH, right?

```
ssh() {
    if [[ -n "$TMUX" ]]; then
        cur="$(tmux display-message -p '#W')"
        tmux rename-window $(parse-ssh-cl "$@" | awk '/^Host/ { print $2; }')
        command ssh "$@"
        tmux rename-window "$cur"
    else
        exec command ssh "$@"
    fi
}
```

## Never Asked Questions.

Do you support `-l` and `-p` parsing? Not yet. That's a great idea me.

## License.

Pretty much all of this code is straight up copy/pasted from
[OpenSSH](https://github.com/openssh/openssh-portable) and the one function from
[OpenBSD](https://github.com/openbsd/src). After reading the entire LICENSE file
from OpenSSH I have concluded that I have no idea if and how I'm supposed to
give attribution.
