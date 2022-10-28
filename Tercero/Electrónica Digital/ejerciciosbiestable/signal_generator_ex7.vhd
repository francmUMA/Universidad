--
-- VHDL Entity work.signal_generator_ex7.arch_name
--
-- Created:
--          by - Fran.UNKNOWN (DESKTOP-IVAGNN6)
--          at - 17:14:55 26/10/2022
--
-- using Mentor Graphics HDL Designer(TM) 2018.2 (Build 19)
--
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;

ENTITY signal_generator_ex7 IS
    port (A, K : out bit);
END ENTITY signal_generator_ex7;

architecture struct of signal_generator_ex7 is
    constant t: time := 60 ns;
begin
    LA: process
        begin
            A <= '0', '1' after T + (10 ns), '0' after 220 ns;
            wait;
    end process;
    LK: process
        begin
            K <= '0', '1' after T / 2;
            wait for T;
    end process;
END struct;