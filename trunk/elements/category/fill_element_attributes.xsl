<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	<xsl:template match="category">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
		
				<xsl:apply-templates select="@*"/>
				<xsl:text disable-output-escaping="yes">
					&lt;attribute name="category_definition" value="</xsl:text>
				<xsl:apply-templates select="ctgr_def"/>
  				<xsl:text disable-output-escaping="yes">"&gt;</xsl:text>



				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>

	
	
	<!-- vypise vsechny atributy -->
	<xsl:template match="@*">
	
					<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
					<attribute name="{name()}" value="{.}" />
	</xsl:template>
	<!-- vypise vsechny atributy -->

	<xsl:template match="ctgr_def">
	<xsl:if test="position()!=1">
  	<xsl:text disable-output-escaping="no">;</xsl:text> 
  	</xsl:if>
  	<xsl:value-of select="@definition" /> 
  	</xsl:template>

	





</xsl:stylesheet>
