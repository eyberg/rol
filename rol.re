load("../reia/lib/file.re")

class StringX
  def initialize(var)
    @txt = var
    @code = ""
    @body = "<html><head><link type='text/css' rel='stylesheet' media='screen' href='main.css'/></head><body><script>function flipit(id) { varel = document.getElementById(id); if(varel.style.display=='') { varel.style.display='none'; } else { varel.style.display = ''; }}</script><div class='header'><center><img src='reia.png'></center></div><br>"
  end

  def code
    @code
  end

  def setcode(stuff)
    @code = stuff
  end

  def body
    @body
  end

  def txt 
    @txt
  end

  def setbody(stuff)
    @body = "#{@body} #{stuff}"
  end

  def settxt(stuff)
    @txt = stuff
  end

  #doesn't support multi-byte yet
  def length
    @txt.to_list().size()
  end

  # same thing as length but no multi-byte support
  def size
    @txt.to_list().size()
  end

  def substr(string, top, bot)
    string::substr(string.to_list(), top, bot).to_string()
  end

  def to_s(list)
    blah = io::format(list)
  end

  def startpos(string, match)
    string::str(string.to_list(), match.to_list())
  end

  def split(string, delim)
    list = string::tokens(string.to_list(), delim.to_list())
  end

  # extract basename from filename
  def basename(name)
    fsize = name.to_list().size()
    rsize = fsize - 2
    rfile = substr(name, 2, rsize)
    delim = "/"
    blah = split(rfile, delim)
    bsize = blah.size() - 1
    rfile = blah[bsize].to_string()
  end

  def pathname(name)
    fsize = name.to_list().size()
    rsize = fsize - 2
    rfile = substr(name, 2, rsize)
  end

end

so = StringX("asdf")

file = System.args().inspect()

if file == "[]"
  puts("Usage:\r\n reia file.re")
else
  path = so.pathname(file)

  try
    blah = File.read(path)
  catch ex
    puts("Cant find file")
    System.halt()
  end

  spos = so.split(blah, "\n")

  rfile = so.basename(file)

  range = 0..spos.size()
  range.map{ |i|
    mod = so.startpos(spos[i], "module")
    defi = so.startpos(spos[i], "def")
    claz = so.startpos(spos[i], "class")

    if mod > 0
      line = spos[i].to_string()
      code = so.code()
      so.setbody("<div onclick=\"flipit('m#{i}');\"><b>Module:</b> #{line}</div><br><div id=\"m#{i}\" class='codeblock' style='display: none;'>#{code}</div>")
      so.setcode("")
    end

    if defi > 0
      line = spos[i].to_string()
      code = so.code()
      so.setbody("<div onclick=\"flipit('d#{i}');\"><b>Method:</b> #{line}</div><br><div id=\"d#{i}\" class='codeblock' style='display: none;'>#{code}</div>")
      so.setcode("")
    end

    if claz > 0
      line = spos[i].to_string()
      code = so.code()
      so.setbody("<div onclick=\"flipit('c#{i}');\"><b>Class:</b> #{line}</div><br><div id=\"c#{i}\" class='codeblock' style='display: none;'>#{code}</div>")
      so.setcode("")
    end

    pcode = so.code()
    so.setcode("#{pcode} <br> #{spos[i].to_list().to_string()}")
  }

  body = so.body()

  File.write("#{rfile}.html", "#{body}")
end
