load("../reia/lib/file.re")

class StringX
  def initialize(var)
    @txt = var
    @body = "<html><body><center><img src='reia.png'></center><br>"
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
path = so.pathname(file)

blah = File.read(path)
spos = so.split(blah, "\n")

rfile = so.basename(file)

range = 0..spos.size()
range.map{ |i|
  mod = so.startpos(spos[i], "module")
  defi = so.startpos(spos[i], "def")
  claz = so.startpos(spos[i], "class")

  if mod > 0
    line = spos[i].to_string()
    so.setbody("<b>Module:</b> #{line}<br><br>")
  end

  if defi > 0
    line = spos[i].to_string()
    so.setbody("<b>Method:</b> #{line}<br><br>")
  end

  if claz > 0
    line = spos[i].to_string()
    so.setbody("<b>Class:</b> #{line}<br><br>")
  end
}

body = so.body()

File.write("#{rfile}.html", "#{body}")
