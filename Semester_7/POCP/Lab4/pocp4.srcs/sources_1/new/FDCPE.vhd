----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 26.10.2024 20:49:27
-- Design Name: 
-- Module Name: FDCPE - Behavioral
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

entity FDCPE is
    Port ( CLK, CLR : in STD_LOGIC;
           EN : in STD_LOGIC;
           D : in STD_LOGIC;
           Q : out STD_LOGIC);
end FDCPE;

architecture Behavioral of FDCPE is
        signal s: std_logic;


begin
    process(CLR, D, EN, CLK)
    begin
        if CLR = '1' then
            s <= '0';  
        elsif EN = '1' then
            if rising_edge(CLK) then
                s <= D;  
            end if;
        end if;
    end process; 
 
 Q <= s;


end Behavioral;
