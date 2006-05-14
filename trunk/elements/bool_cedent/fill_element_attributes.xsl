<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	<xsl:template match="bool_cedent">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
		
				<xsl:apply-templates select="@*"/>
<!--				
				<xsl:text disable-output-escaping="yes">
					&lt;attribute name="categories" value="</xsl:text> 
  				<xsl:apply-templates select="ctgr" /> 
  				<xsl:text disable-output-escaping="yes">"/&gt;</xsl:text>
  
  				<xsl:text disable-output-escaping="yes">
  					&lt;attribute name="missing_values" value="</xsl:text> 
  				<xsl:apply-templates select="missing_value" /> 
  				<xsl:text disable-output-escaping="yes">" /&gt;</xsl:text>
-->

				<xsl:apply-templates select="sub_bool_cedent" mode="recurent_scan" />


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


	<xsl:template match="node()" mode="recurent_scan">
		<xsl:param name="name_prefix" /> 

		<xsl:apply-templates select="@*">
			<xsl:with-param name="name_prefix">
  				<xsl:value-of select="$name_prefix" />
  				<xsl:value-of select="name()" />
  				<xsl:value-of select="position()" />
  				<xsl:text>_</xsl:text>
  			</xsl:with-param>
		</xsl:apply-templates>
		
		<xsl:apply-templates select="*" mode="recurent_scan">
			<xsl:with-param name="name_prefix">
  				<xsl:value-of select="$name_prefix" />
  				<xsl:value-of select="name()" />
  				<xsl:value-of select="position()" />
  				<xsl:text>_</xsl:text>
  			</xsl:with-param>
		</xsl:apply-templates>
    </xsl:template>
    
</xsl:stylesheet>
