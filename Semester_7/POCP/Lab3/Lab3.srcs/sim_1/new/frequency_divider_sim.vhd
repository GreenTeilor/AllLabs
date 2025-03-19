library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity frequency_divider_sim is
end frequency_divider_sim;

architecture Behavioral of frequency_divider_sim is
component frequency_divider
    port(
        clk, clr: in std_logic;
        div2, div4, div8: out std_logic
    );
end component;        
signal clk : std_logic := '0'; 
signal clr : std_logic := '0';  
signal div2 : std_logic;       
signal div4 : std_logic;        
signal div8 : std_logic;                     
constant clk_period : time := 10 ns;      
begin 

U1 : frequency_divider port map (clk=>clk, clr=>clr, div2=>div2, div4=>div4, div8=>div8);

CLK_PROCESS : process
begin
  while true loop
    clk <= '0';
    wait for clk_period/2;
    clk <= '1';
    wait for clk_period/2;
  end loop;
 end process;
    
 STIM_PROC: process
 begin 
   wait for 20 ns;
   clr <= '1';
   wait for 20 ns;
   clr <= '0';     
   wait for 1000 ns;
   wait;
 end process;
 
end Behavioral;
