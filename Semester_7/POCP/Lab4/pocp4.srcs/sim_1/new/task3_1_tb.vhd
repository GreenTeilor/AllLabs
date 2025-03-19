library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task3_1_tb is
end task3_1_tb;

architecture Behavioral of task3_1_tb is
component task3_1
  port (
   CLK: in std_logic;
   RST: in std_logic;   
   Pout: out std_logic_vector(0 to 3)
   );
 end component;
 signal CLK: std_logic := '0';
 signal RST: std_logic := '1';
 
 signal Pout: std_logic_vector(0 to 3);
 constant clock_period : time := 10 ns;
begin
 UUT: task3_1 port map (
  CLK => CLK,
  RST => RST,  
  POut => POut
  );
 
 CLK <= not CLK after clock_period;
 
 reset: process
 begin
  RST <= '1';
  wait for clock_period;
  RST <= '0';
  wait for clock_period * 20;
 end process;




end Behavioral;
