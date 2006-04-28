<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	<xsl:template match="attribute">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
		
				<xsl:apply-templates select="@*"/>
				
				<xsl:text disable-output-escaping="yes">
					&lt;attribute name="categories" value="</xsl:text> 
  				<xsl:apply-templates select="ctgr" /> 
  				<xsl:text disable-output-escaping="yes">"&gt;</xsl:text>
  
  				<xsl:text disable-output-escaping="yes">
  					&lt;attribute name="missing_values" value="</xsl:text> 
  				<xsl:apply-templates select="missing_value" /> 
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



	<xsl:template match="ctgr">
    <xsl:if test="position()!=1">
    <xsl:text disable-output-escaping="no">;</xsl:text> 
    </xsl:if>
    <xsl:value-of select="@name" /> 
    </xsl:template>

    <xsl:template match="missing_value">
    <xsl:if test="position()!=1">
    <xsl:text disable-output-escaping="no">;</xsl:text> 
    </xsl:if>
    <xsl:value-of select="@name" /> 
    </xsl:template>




</xsl:stylesheet>
