
entity elem is
  port ( A, K : in bit;
            C : out bit );
end Elem;

architecture Descripc of elem is
  signal R : bit := '0';
  signal Eo : bit := '0';
begin
  L1: Eo <= R xor A;
  L2: C <= R;
  L3: process
    begin
      if K = '1' then
        R <= Eo;
      end if;
      wait on k;
  end process;
end Descripc;