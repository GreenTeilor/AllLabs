----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 26.10.2024 17:04:07
-- Design Name: 
-- Module Name: D_trigger - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity D_trigger is
    Port ( D : in STD_LOGIC;
           CLK : in STD_LOGIC;
           EN : in STD_LOGIC;
           Q : out STD_LOGIC);
end D_trigger;

architecture Behavioral of D_trigger is
        signal result: std_logic;

begin
    process(CLK)
    begin
        if EN = '1' then
            if rising_edge(CLK) then
                result <= D;
            end if;
        end if;
    end process;
Q <= result;
    
end Behavioral;
