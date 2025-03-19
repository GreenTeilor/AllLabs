library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task3_LFSR_Out_tb is
    Generic(n : integer := 3);
end task3_LFSR_Out_tb;

architecture Behavioral of task3_LFSR_Out_tb is
component task3_LFSR_out     
  generic (N : integer := 3);
  port(
   CLK: in std_logic;
   RST: in std_logic; 
   Pout: out std_logic_vector(0 to N-1)
   );
 end component;
 signal CLK: std_logic := '0';
 signal RST: std_logic := '0'; 
 
 signal Pout: std_logic_vector(0 to N-1);
 constant clock_period: time := 10 ns;
begin
 uut: task3_LFSR_out port map (
  CLK => CLK,
  RST => RST,  
  POut => POut
  );
  CLK <= not CLK after clock_period;
end Behavioral;
