library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task3_LFSR_out is
    Generic(N: integer := 3;
            init_state : std_logic_vector := "111");
    Port ( CLK : in STD_LOGIC;
           RST : in STD_LOGIC;
           Pout : out STD_LOGIC_VECTOR(0 to N-1));
end task3_LFSR_out;

architecture Behavioral of task3_LFSR_out is
signal register_state: std_logic_vector(0 to N-1) := init_state;
signal new_bit: std_logic := '0';
Begin
 Main: process (CLK, RST)
 variable new_bit: std_logic := '0';
 begin
  if RST = '1' then
     register_state <= init_state;
  elsif rising_edge(CLK) then
     new_bit := register_state(0) xor register_state(N-1);
     register_state <= new_bit & register_state(0 to N-2);
  end if;
 end process; 
 Pout <= register_state;
end Behavioral;
