library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task3_signature is
 Generic(N: integer := 3;
           init_state : std_logic_vector := "111");
   Port ( CLK : in STD_LOGIC;
          RST : in STD_LOGIC;
          Pin: in std_logic;
          Pout : out STD_LOGIC_VECTOR(0 to N-1));
end task3_signature;

architecture Behavioral of task3_signature is

signal register_state: std_logic_vector(0 to N-1) := init_state;
       
Begin
 Main: process (CLK, RST)
 variable zero_bit: std_logic := '0'; 
 variable new_bit: std_logic := '0';
 begin
  if RST = '1' then
   register_state <= init_state;
  elsif rising_edge(CLK) then
    for i in 0 to N-1 loop
        zero_bit := zero_bit or register_state(i);
    end loop;
    zero_bit := not zero_bit; 
    new_bit := zero_bit xor register_state(0) xor register_state(N-1);
     register_state <= (new_bit xor Pin) & register_state(0 to N-2);
    end if;
 end process; 
 Pout <= register_state;
end Behavioral;
