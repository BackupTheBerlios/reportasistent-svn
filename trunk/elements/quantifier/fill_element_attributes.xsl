<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	<xsl:template match="quantifier">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
		
				<xsl:apply-templates select="@*"/>
				

				<xsl:for-each select="quant_item">
				
					<xsl:call-template name="quant_item_template"/>					
					
				</xsl:for-each>


				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>

	
	
	<!-- vypise vsechny atributy krome ID-->
	<xsl:template match="@*">
		<xsl:param name="name_prefix" /> 

					<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
					<attribute name="{$name_prefix}{name()}" value="{.}" />
	</xsl:template>
	<!-- vypise vsechny atributy -->

	
	
	<!--atribut ID se ignoruje-->
	<xsl:template match="@id">
	</xsl:template>
	

    
    
    <xsl:template name="quant_item_template">
		
					<xsl:text disable-output-escaping="yes">
					</xsl:text>		
		<attribute name="{@name}" value="{@value}" />		
		
	</xsl:template>
    
</xsl:stylesheet>
