program kot;

var ch:char;
procedure setup;
begin
  assign(input,'kot.in');
  reset(input);
  assign(output,'kot.out');
  rewrite(output)
end;
procedure endit;
begin
  close(input);
  close(output)
end;
begin
  setup;
  while not eoln do
    begin
      read(ch);
      case ch of
        '`','1','2','3','4','5','6','7','8','9','0','-','=':write(1);
        'Q','W','E','R','T','Y','U','I','O','P','[',']','\':write(2);
        'A','S','D','F','G','H','J','K','L',';','''':write(3);
        'Z','X','C','V','B','N','M',',','.','/':write(4);
        ' ':write(5);
      end;
    end;
  writeln;
  endit;
end.

