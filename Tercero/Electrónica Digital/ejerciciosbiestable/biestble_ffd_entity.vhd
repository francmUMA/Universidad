--
-- VHDL Entity work.biestble_ffd.arch_name
--
-- Created:
--          by - Fran.UNKNOWN (DESKTOP-IVAGNN6)
--          at - 20:11:27 27/10/2022
--
-- using Mentor Graphics HDL Designer(TM) 2018.2 (Build 19)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

-- VHDL DECLARATION OF D_FF :
ENTITY biestble_ffd_entity IS
    PORT (d, rst, clk : IN std_logic; q: OUT std_logic);
END biestble_ffd_entity;
-- 
-- COMPLETE VHDL DESCRIPTION FOR THE D_FF :

ARCHITECTURE behavioral OF biestble_ffd_entity IS
BEGIN
dff: PROCESS (rst, clk)
BEGIN
      IF rst = '1' THEN
           q <= '0';
      ELSIF clk = '1' AND clk'EVENT THEN
           q <= d;
      END IF;
END PROCESS dff;
END behavioral;

---

