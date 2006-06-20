<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
    
    
    <!-- definovani klice - dulezite kvuli hledani elementu s danym ID v celem dokumentu -->
    <xsl:key name="attribute_id" match="ti_attribute" use="@id" />
    
          
	
	<xsl:template match="hyp_sdcf">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
				<!-- vygenerovani atributu -->
				
				<xsl:apply-templates select="@*"/>

				<!-- vygenerovani hodnot kontingencni tabulky -->
				
				
				<xsl:variable name="kategorie" >	
					<xsl:value-of select="@attributes" />
				</xsl:variable>
				
				
				<xsl:for-each select="r" >
				<xsl:variable name="cislo_tabulky" select="position()" />
				
				   
				   <xsl:for-each select="c">  <!-- cyklus pres polozky radku-->
				   		<xsl:variable name="cislo_sloupce" select="position()" />
				   		<xsl:variable name="jmeno" >
				   				<xsl:text>Tab</xsl:text>
				   				<xsl:value-of select="$cislo_tabulky" />
				   				<xsl:text>(</xsl:text>
				   				<xsl:value-of select="key('attribute_id' , $kategorie)/ti_category[$cislo_sloupce]/@value" />
				   				<xsl:text>)</xsl:text>
				   		</xsl:variable>
				   		
				   		<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
						<attribute name="{$jmeno}" value="{@val}" />
				   
				   </xsl:for-each>
				   
				</xsl:for-each>
				
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>


	
	<!-- vypise vsechny atributy krome cedentu-->
	
	<xsl:template match="@*">
	
					<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
					<attribute name="{name()}" value="{.}" />
	</xsl:template>
	
	



	<!-- zpracovani cedentu-->
	
	<xsl:template match="@attributes | @condition | @set1 | @set2">
		
		<xsl:apply-templates select="id(.)" mode="values" />		

	</xsl:template>
	
	
	

	

	<!-- boolske literaly -> cedent -->
	<xsl:template match="ti_cedent" mode="values">		
    	<xsl:variable name="hodnota_cedentu">
    		<xsl:apply-templates select="ti_literal" mode="values"/>
    	</xsl:variable>
    	<xsl:text disable-output-escaping="yes">
					</xsl:text>		
    	<attribute name="{@type}" value="{$hodnota_cedentu}" />	
	</xsl:template>
	
	
	
	<!-- kategorialni cedent -->
	<xsl:template match="ti_attribute" mode="values">
		<xsl:text disable-output-escaping="yes">
					</xsl:text>		
    	<attribute name="{@type}" value="{@quant}" />
	</xsl:template>
	

	<!-- preformatuje boolsky literal -->
	<xsl:template match="ti_literal" mode="values">		
		
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no"> &amp; </xsl:text>
		</xsl:if>

		
		<xsl:value-of select="@quant"/>
		<xsl:text disable-output-escaping="yes">(</xsl:text>
		<xsl:value-of select="@value"/>
		<xsl:text disable-output-escaping="yes">)</xsl:text>
	</xsl:template>
	






</xsl:stylesheet>
