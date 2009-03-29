load("../reia/lib/file.re")
load("rolh.re")

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
      rol.setbody("<div class='subheader' onmouseover=\"this.style.backgroundColor='#dedede';\"; onmouseout=\"this.style.backgroundColor='';\"; onclick=\"flipit('m#{i}');\"><b>Module:</b> #{line}</div><br><div id=\"m#{i}\" class='codeblock' style='display: none;'>")
      rol.setcbegin(1)
    end

    if defi > 0
      if rol.cbegin() > 0
        code = rol.code()
        rol.setbody("#{code}</div>")
        rol.setcode("")
      end
 
      line = spos[i].to_string()
      rol.setbody("<div class='subheader' onmouseover=\"this.style.backgroundColor='#dedede';\"; onmouseout=\"this.style.backgroundColor='';\"; onclick=\"flipit('d#{i}');\"><b>Method:</b> #{line}</div><br><div id=\"d#{i}\" class='codeblock' style='display: none;'>")
      rol.setcbegin(1)
    end

    if claz > 0
      if rol.cbegin() > 0
        code = rol.code()
        rol.setbody("#{code}</div>")
        rol.setcode("")
      end

      line = spos[i].to_string()
      rol.setbody("<div class='subheader' onmouseover=\"this.style.backgroundColor='#dedede';\"; onmouseout=\"this.style.backgroundColor='';\"; onclick=\"flipit('c#{i}');\"><b>Class:</b> #{line}</div><br><div id=\"c#{i}\" class='codeblock' style='display: none;'>")
      rol.setcbegin(1)
    end

   pcode = rol.code()
   scode = spos[i].to_list().to_string()
   #scode = rol.asciiToHtml(scode)

   rol.setcode("#{pcode} <br> #{scode}")
 }

  body = rol.body()

  File.write("#{rfile}.html", "#{body}")

end
