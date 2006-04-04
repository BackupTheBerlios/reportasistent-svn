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



	<!-- naplni hodnotu cedentu-->
	<xsl:template match="@antecedent | @succedent | @condition">
	
					<!-- zapise: <attribute name="{name()}" value="-->

					<xsl:text disable-output-escaping="yes">
					&lt;attribute name="</xsl:text>

					<xsl:value-of select="name()"/>
					
					<xsl:text disable-output-escaping="yes">" value="</xsl:text>
		
		

					<!-- zapise hodnotu cedentu -->
					<xsl:apply-templates select="id(.)" mode="values"/>


					<xsl:text disable-output-escaping="yes">" /&gt;</xsl:text>

	</xsl:template>
	



	<!-- literaly -> cedent -->
	<xsl:template match="ti_cedent" mode="values">		
    	<xsl:apply-templates select="ti_literal" mode="values"/>
	</xsl:template>
	

	<!-- preformatuje literal -->
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
