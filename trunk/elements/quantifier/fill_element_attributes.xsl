<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	<xsl:template match="quantifier">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
		
				<xsl:apply-templates select="@*"/>
				
			<!--	<xsl:apply-templates select="basic_quantifier" mode="recurent_scan" /> -->
				<xsl:for-each select="basic_quantifier">
				
					<xsl:call-template name="basic_quant_template"/>
					
					
				</xsl:for-each>


				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>

	
	
	<!-- vypise vsechny atributy -->
	<xsl:template match="@*">
		<xsl:param name="name_prefix" /> 

					<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
					<attribute name="{$name_prefix}{name()}" value="{.}" />
	</xsl:template>
	<!-- vypise vsechny atributy -->


	<xsl:template name="basic_quant_template">
		<xsl:param name="name_prefix" /> 

		<xsl:variable name="element_name" select="name()" />
		<xsl:variable name="element_position" select="position()" />
		
		<xsl:apply-templates select="@*">
			<xsl:with-param name="name_prefix">
  				<xsl:value-of select="$element_name" />
  				<xsl:value-of select="$element_position" />
  				<xsl:text>_</xsl:text>
  			</xsl:with-param>
		</xsl:apply-templates>
		
		<xsl:for-each select="quant_item">
			<xsl:call-template name="quant_item_template">
				<xsl:with-param name="name_prefix">
  					<xsl:value-of select="$element_name" />
  					<xsl:value-of select="$element_position" />
  					<xsl:text>_</xsl:text>
  				</xsl:with-param>
			</xsl:call-template>
			
			
			
		</xsl:for-each>
		
    </xsl:template>
    
    
    <xsl:template name="quant_item_template">
		<xsl:param name="name_prefix" /> 
		
					<xsl:text disable-output-escaping="yes">
					</xsl:text>		
		<attribute name="{$name_prefix}{@name}" value="{@value}" />		
		
	</xsl:template>
    
</xsl:stylesheet>
