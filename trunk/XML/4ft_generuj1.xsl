<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
      
	
	
	<!-- tohle prijde predelat - jen pro ladeni 
	<xsl:template match="/active_list">
		<xsl:apply-templates select="hyp_4ft[position()=1]"/>
	</xsl:template>
      -->
      
	
	
	


	<xsl:template match="hyp_4ft"> <!-- nezpomen prepsat na match="/hyp_4ft" - odebrat lomitko -->

<xsl:text>
</xsl:text>				

		<chapter title="Vygenerovaná 4FT hypotéza ({@id} - {@db_name})">
	

			<xsl:apply-templates select="id(@antecedent)"/>
			<xsl:apply-templates select="id(@succedent)"/>
			<xsl:apply-templates select="id(@condition)"/>


<xsl:text>
</xsl:text>				

		</chapter>

	</xsl:template>
	



	


	<xsl:template match="ti_cedent">
<xsl:text>
	</xsl:text>
		<paragraph>


<xsl:text>
		</xsl:text>
		
		<text>
			<xsl:value-of select="@type"/>:<br/>			
			<xsl:apply-templates select="ti_literal"/>
		</text>

<xsl:text>
	</xsl:text>
		</paragraph>
	</xsl:template>
	
	



	<xsl:template match="ti_literal">
		<xsl:if test="position()!=1">
			<br/>
		</xsl:if>

		<xsl:value-of select="@quant"/>:<tab/><xsl:value-of select="@value"/>
						
	
	</xsl:template>
      




</xsl:stylesheet>
