load("rolh.re")

so = Rol("test")
#newstr = so.txt()
#puts(newstr)

## list to string test
#list = [104, 101, 108, 108, 111]
#so.to_s(list)

## substring test
puts("testing strpos()")
sub = "hello world!"
sub = so.substr(sub, 4, 8)
puts(sub)
puts("\r\n")

## strpos stest
puts("testing strpos()")
string = "hack the world"
world = so.startpos(string, " ")
puts(world)
puts("\r\n")

## split test
puts("testing split()")
string = "hack the planet"
world = so.split(string, " ")
puts(world[0])
puts(world[1])
puts(world[2])
puts("\r\n")
