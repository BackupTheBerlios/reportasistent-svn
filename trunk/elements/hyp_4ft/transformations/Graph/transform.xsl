<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xl3DColumn</xsl:variable>
<xsl:variable name="GraphTitle">4ft Graph</xsl:variable>
<xsl:variable name="LegendShow">false</xsl:variable>
<xsl:variable name="GraphWidth">1</xsl:variable>
<xsl:variable name="GraphHeight">0,75</xsl:variable>

	
	


	<xsl:template match="hyp_4ft"> <!-- nezpomen prepsat na match="/hyp_4ft" - odebrat lomitko -->

		<paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_4ftgraph">
				<categories id="categories1">
					<category title="succedent" id="category1"></category>
					<category title="not succedent" id="category2"></category>
				</categories>
				<chart title="antecend" id="chart1">
					<value value="{@a}" id="value1"></value>
					<value value="{@b}" id="value2"></value>
				</chart>			
				<chart title="not antecend" id="chart2">
					<value value="{@c}" id="value3"></value>
					<value value="{@d}" id="value4"></value>
				</chart>			
			</graph>
		</paragraph>						
	
	</xsl:template>
      




</xsl:stylesheet>
