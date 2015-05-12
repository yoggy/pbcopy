pbcopy.exe
====
pbcopy command for windows.

  > echo abc1234 | pbcopy.exe    # copy "abc1234" to the clipboard.

inspired by ...
----
* pbcopy(1)
  * https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man1/pbcopy.1.html


conclusion
----
see also clip.exe

  C:\>clip.exe /?
  
  CLIP
  
  Description:
      Redirects output of command line tools to the Windows clipboard.
      This text output can then be pasted into other programs.
  
  Parameter List:
      /?                  Displays this help message.
  
  Examples:
      DIR | CLIP          Places a copy of the current directory
                          listing into the Windows clipboard.
  
      CLIP < README.TXT   Places a copy of the text from readme.txt
                          on to the Windows clipboard.
  
