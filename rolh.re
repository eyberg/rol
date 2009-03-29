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
    @tstr = ""
    @cbegin = 0
    @body = ""
    
    readmarkup()
    
  end

  def readmarkup
    @body = File.read("markup/header.html")
  end

  #loads in markup for a specified file
  #returns said markup
  def loadmarkup(file)
    blah = File.read(file)
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

  # convert ascii to html characters
  def asciiToHtml(stuff)

    # four space
    #blah = split(stuff, "    ")
    #blah = blah.map{|i| i.to_string()}.join("&nbsp;&nbsp;&nbsp;&nbsp;")

    # two space
    #blah = split(blah, "  ")
    #blah = blah.map{|i| i.to_string()}.join("&nbsp;&nbsp;")

    "blah"
    # spaces
    #blah = split(blah, " ")
    #blah = blah.map{|i| i.to_string()}.join("&nbsp;")

    # tabs
    #blah = split(blah, "\t")
    #blah = blah.map{|i| i.to_string()}.join("&nbsp;&nbsp;")
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
