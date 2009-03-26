load("../reia/lib/file.re")

# helper class for the doc project..
# this has evolved from a string class
# that I wanted for helper methods like
# substr and the like
class Rol

  # class instantiation
  def initialize(var)
    dt = datetime()
    @code = ""
    @cbegin = 0
    @body = "<html><head><link type='text/css' rel='stylesheet' media='screen' href='main.css'/></head><body><script>function flipit(id) { varel = document.getElementById(id); if(varel.style.display=='') { varel.style.display='none'; } else { varel.style.display = ''; }}</script><div class='header'><center><img src='reia.png'></center><div class='hlink'><a href=\"http://wiki.reia-lang.org/wiki/Reia_Programming_Language\">Reia WebSite</a></div><div class='datetime'>Generated: #{dt}</div><div class='clearboth'></div></div><br>"
  end

  # getter for code class instance var
  def code
    @code
  end

  # setter for code class instance var
  def setcode(stuff)
    @code = stuff
  end

  def setcbegin(val)
    @cbegin = val
  end

  def cbegin
    @cbegin
  end

  # getter for body class instance var
  # until we do something w/haml or whatever
  # this holds the generated html markup
  def body
    @body
  end

  # setter for markup
  def setbody(stuff)
    @body = "#{@body} #{stuff}"
  end

  # shorthand for erlang's substring; note that 'end' is
  # reserved in Reia
  def substr(string, top, bot)
    string::substr(string.to_list(), top, bot).to_string()
  end

  # return the position of first occurence of match in string
  # overloads erlang's string::str() method
  def startpos(string, match)
    string::str(string.to_list(), match.to_list())
  end

  # splits string into a list of tokens delimited by delim
  # overloads elrang's string::tokens() method 
  def split(string, delim)
    list = string::tokens(string.to_list(), delim.to_list())
  end

  # extract basename from filename
  # takes out directory path (like '.../reia/lib/')
  def basename(name)
    fsize = name.to_list().size()
    rsize = fsize - 2
    rfile = substr(name, 2, rsize)
    delim = "/"
    blah = split(rfile, delim)
    bsize = blah.size() - 1
    rfile = blah[bsize].to_string()
  end

  # pull out erlang datetime
  def datetime
    date = erlang::date()
    time = erlang::time()
    blah = "#{date.to_s()} #{time.to_s()}"
  end

  # extracts pathname from System.args
  # basically just removes the brackets..
  # not sure what's going on there..
  def pathname(name)
    fsize = name.to_list().size()
    rsize = fsize - 2
    rfile = substr(name, 2, rsize)
  end

end

rol = Rol("asdf")

file = System.args().inspect()

if file == "[]"
  puts("Usage:\r\n reia file.re")
else
  path = rol.pathname(file)

  try
    blah = File.read(path)
  catch ex
    puts("Cant find file")
    System.halt()
  end

  spos = rol.split(blah, "\n")

  rfile = rol.basename(file)

  range = 0..spos.size()
  range.map{ |i|
    mod = rol.startpos(spos[i], "module")
    defi = rol.startpos(spos[i], "def")
    claz = rol.startpos(spos[i], "class")

    if mod > 0
      if rol.cbegin() > 0
        code = rol.code()
        rol.setbody("#{code}</div>")
        rol.setcode("")
      end
 
      line = spos[i].to_string()
      rol.setbody("<div class='subheader' onclick=\"flipit('m#{i}');\"><b>Module:</b> #{line}</div><br><div id=\"m#{i}\" class='codeblock' style='display: none;'>")
      rol.setcbegin(1)
    end

    if defi > 0
      if rol.cbegin() > 0
        code = rol.code()
        rol.setbody("#{code}</div>")
        rol.setcode("")
      end
 
      line = spos[i].to_string()
      rol.setbody("<div class='subheader' onclick=\"flipit('d#{i}');\"><b>Method:</b> #{line}</div><br><div id=\"d#{i}\" class='codeblock' style='display: none;'>")
      rol.setcbegin(1)
    end

    if claz > 0
      if rol.cbegin() > 0
        code = rol.code()
        rol.setbody("#{code}</div>")
        rol.setcode("")
      end

      line = spos[i].to_string()
      rol.setbody("<div class='subheader' onclick=\"flipit('c#{i}');\"><b>Class:</b> #{line}</div><br><div id=\"c#{i}\" class='codeblock' style='display: none;'>")
      rol.setcbegin(1)
    end

   pcode = rol.code()
   rol.setcode("#{pcode} <br> #{spos[i].to_list().to_string()}")
 }

  body = rol.body()

  File.write("#{rfile}.html", "#{body}")
end
